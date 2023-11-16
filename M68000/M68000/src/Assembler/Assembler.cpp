#include <cstdint>

#include "M68000/Assembler.h"
#include "M68000/AssemblerImpl.h"

namespace {

using namespace rbrown::m68000;

class Line {
public:
    explicit Line(const std::string&);
    [[nodiscard]] bool MatchNumberPrefixOrDigit() const;
    [[nodiscard]] bool MatchChar(char) const;
    bool MatchCharAndAdvance(char);
    bool MatchWhiteSpaceAndAdvance();
    bool MatchCommaAndWhiteSpaceAndAdvance();
    bool MatchNumberAndAdvance(int base, int64_t& result);
    [[nodiscard]] bool MatchEnd() const;
private:
    const std::string& line;
    std::string::size_type pos;
};

Line::Line(const std::string& l) : line(l), pos(0) {}

bool Line::MatchNumberPrefixOrDigit() const {
    if (pos < line.size()) {
        const auto c = line[pos];
        if (c == '-' || c == '+' || std::isdigit(c)) {
            return true;
        }
    }
    return false;
}

bool Line::MatchChar(char c) const {
    if (pos < line.size()) {
        return line[pos] == c;
    }
    return false;
}

bool Line::MatchCharAndAdvance(char c) {
    if (MatchChar(c)) {
        ++pos;
        return true;
    }
    return false;
}

bool Line::MatchWhiteSpaceAndAdvance() {
    return MatchCharAndAdvance(' ');
}

bool Line::MatchCommaAndWhiteSpaceAndAdvance() {
    if (MatchCharAndAdvance(',')) {
        if (MatchCharAndAdvance(' ')) {
            return true;
        }
    }
    return false;
}

bool Line::MatchNumberAndAdvance(int base, int64_t& result) {
    if (pos < line.size()) {
        size_t idx;
        result = std::stoll(line.c_str() + pos, &idx, base);
        pos += idx;
        return true;
    }
    return false;
}

bool Line::MatchEnd() const {
    return pos == line.size();
}

bool AssembleNumber(Line& line, int64_t& number) {
    return line.MatchNumberAndAdvance(0, number);
}

bool AssembleRegisterNumber(Line& line, int64_t& number) {
    int64_t digit {};
    if (line.MatchNumberAndAdvance(10, digit)) {
        if (digit >= 0 && digit < 8) {
            number = digit;
            return true;
        }
    }
    return false;
}

bool AssembleAddressRegister(Line& line, int64_t& number) {
    if (line.MatchCharAndAdvance('A')) {
        return AssembleRegisterNumber(line, number);
    }
    return false;
}

bool AssembleAddressRegisterDirect(Line& line, AddressModeData& mode) {
    // An
    int64_t number;
    if (AssembleAddressRegister(line, number)) {
        mode.SetMode(AddressModes::ADDRESS_DIRECT);
        mode.SetRegisterNumber(number);
        return true;
    }
    return false;
}

bool AssembleDataRegister(Line& line, int64_t& number) {
    if (line.MatchCharAndAdvance('D')) {
        return AssembleRegisterNumber(line, number);
    }
    return false;
}

bool AssembleDataRegisterDirect(Line& line, AddressModeData& mode) {
    // Dn
    int64_t number;
    if (AssembleDataRegister(line, number)) {
        mode.SetMode(AddressModes::DATA_DIRECT);
        mode.SetRegisterNumber(number);
        return true;
    }
    return false;
}

bool AssembleSize(Line& line, OperandSizes& size) {
    if (line.MatchCharAndAdvance('.')) {
        if (line.MatchCharAndAdvance('B')) {
            size = OperandSizes::BYTE;
            return true;
        } else if (line.MatchCharAndAdvance('W')) {
            size = OperandSizes::WORD;
            return true;
        } else if (line.MatchCharAndAdvance('L')) {
            size = OperandSizes::LONG;
            return true;
        }
    }
    return false;
}

bool AssembleAbsolute(Line& line, int64_t address, AddressModeData& mode) {
    // (XXX).W, (XXX).L
    OperandSizes size{};
    if (AssembleSize(line, size)) {
        if (size == OperandSizes::WORD) {
            // (XXX).W
            mode.SetMode(AddressModes::ABSOLUTE_SHORT);
            mode.SetAbsoluteAddress(address);
            return true;
        } else if (size == OperandSizes::LONG) {
            // (XXX).L
            mode.SetMode(AddressModes::ABSOLUTE_LONG);
            mode.SetAbsoluteAddress(address);
            return true;
        }
    }
    return false;
}

bool AssembleAddressRegisterIndirectOrPostIncrement(Line& line, AddressModeData& mode) {
    // (An), (An)+
    int64_t number;
    if (AssembleAddressRegister(line, number)) {
        if (line.MatchCharAndAdvance(')')) {
            if (line.MatchCharAndAdvance('+')) {
                mode.SetMode(AddressModes::ADDRESS_INCREMENT);
            } else {
                mode.SetMode(AddressModes::ADDRESS_INDIRECT);
            }
            mode.SetRegisterNumber(number);
            return true;
        }
    }
    return false;
}

bool AssembleIndexRegisterSize(Line& line, IndexRegisterSizes& size) {
    if (line.MatchCharAndAdvance('.')) {
        if (line.MatchCharAndAdvance('W')) {
            size = IndexRegisterSizes::WORD;
            return true;
        } else if (line.MatchCharAndAdvance('L')) {
            size = IndexRegisterSizes::LONG;
            return true;
        }
    }
    return false;
}

bool AssembleIndexRegister(
    Line& line,
    IndexRegisterTypes& type,
    IndexRegisterSizes& size,
    int64_t& number) {
    if (AssembleDataRegister(line, number)) {
        if (AssembleIndexRegisterSize(line, size)) {
            type = IndexRegisterTypes::DATA;
            return true;
        }
    }
    if (AssembleAddressRegister(line, number)) {
        if (AssembleIndexRegisterSize(line, size)) {
            type = IndexRegisterTypes::ADDRESS;
            return true;
        }
    }
    return false;
}

bool AssembleAddressRegisterIndirectWithDisplacementOrIndex(
    Line& line,
    int64_t number,
    AddressModeData& mode) {
    // (d16, An), (d8, An, Xn)
    int64_t addressRegister;
    if (AssembleAddressRegister(line, addressRegister)) {
        if (line.MatchCharAndAdvance(')')) {
            // (d16, An)
            mode.SetMode(AddressModes::ADDRESS_DISPLACEMENT);
            mode.SetRegisterNumber(addressRegister);
            mode.SetDisplacement(number);
            return true;
        } else if (line.MatchCommaAndWhiteSpaceAndAdvance()) {
            // (d8, An, Xn)
            IndexRegisterTypes indexType{};
            IndexRegisterSizes indexSize{};
            int64_t indexRegister;
            if (AssembleIndexRegister(line, indexType, indexSize, indexRegister)) {
                if (line.MatchCharAndAdvance(')')) {
                    mode.SetMode(AddressModes::ADDRESS_INDEX);
                    mode.SetRegisterNumber(addressRegister);
                    mode.SetIndexRegister(indexType, indexSize, indexRegister);
                    mode.SetIndex(number);
                    return true;
                }
            }
        }
    }
    return false;
}

bool AssembleProgramCounterIndirectWithDisplacementOrIndex(
    Line& line,
    int64_t number,
    AddressModeData& mode) {
    // (d16, PC), (d8, PC, Xn)
    if (line.MatchCharAndAdvance('P') && line.MatchCharAndAdvance('C')) {
        if (line.MatchCharAndAdvance(')')) {
            // (d16, PC)
            mode.SetMode(AddressModes::PROGRAM_COUNTER_DISPLACEMENT);
            mode.SetDisplacement(number);
            return true;
        } else if (line.MatchCommaAndWhiteSpaceAndAdvance()) {
            // (d8, PC, Xn)
            IndexRegisterTypes indexType{};
            IndexRegisterSizes indexSize{};
            int64_t indexRegister;
            if (AssembleIndexRegister(line, indexType, indexSize, indexRegister)) {
                if (line.MatchCharAndAdvance(')')) {
                    mode.SetMode(AddressModes::PROGRAM_COUNTER_INDEX);
                    mode.SetIndexRegister(indexType, indexSize, indexRegister);
                    mode.SetIndex(number);
                    return true;
                }
            }
        }
    }
    return false;
}

bool AssembleIndirectOrAbsolute(Line& line, AddressModeData& mode) {
    if (line.MatchChar('A')) {
        // (An), (An)+
        return AssembleAddressRegisterIndirectOrPostIncrement(line, mode);
    } else if (line.MatchNumberPrefixOrDigit()) {
            // (d16, An), (d8, An, Xn)
            // (d16, PC), (d8, PC, Xn)
            // (XXX).W, (XXX).L
            int64_t number;
            if (AssembleNumber(line, number)) {
                if (line.MatchCommaAndWhiteSpaceAndAdvance()) {
                    if (line.MatchChar('A')) {
                        // (d16, An), (d8, An, Xn)
                        return AssembleAddressRegisterIndirectWithDisplacementOrIndex(line, number, mode);
                    } else if (line.MatchChar('P')) {
                        // (d16, PC), (d8, PC, Xn)
                        return AssembleProgramCounterIndirectWithDisplacementOrIndex(line, number, mode);
                    }
                } else if (line.MatchCharAndAdvance(')')) {
                    // (XXX).W, (XXX).L
                    return AssembleAbsolute(line, number, mode);
            }
        }
    }
    return false;
}

bool AssembleAddressRegisterIndirectWithPreDecrement(Line& line, AddressModeData& mode) {
    // -(An)
    int64_t number;
    if (AssembleAddressRegister(line, number)) {
        if (line.MatchCharAndAdvance(')')) {
            mode.SetMode(AddressModes::ADDRESS_DECREMENT);
            mode.SetRegisterNumber(number);
            return true;
        }
    }
    return false;
}

bool AssembleImmediate(Line& line, AddressModeData& mode) {
    // #number
    int64_t immediate;
    if (AssembleNumber(line, immediate)) {
        mode.SetMode(AddressModes::IMMEDIATE);
        mode.SetImmediate(immediate);
        return true;
    }
    return false;
}

bool AssembleCCR(Line& line, AddressModeData& mode) {
    // CCR
    if (line.MatchCharAndAdvance('C')
        && line.MatchCharAndAdvance('C')
        && line.MatchCharAndAdvance('R')) {
        mode.SetMode(AddressModes::CONDITION_CODE_REGISTER);
        return true;
    }
    return false;
}

bool AssembleSR(Line& line, AddressModeData& mode) {
    // SR
    if (line.MatchCharAndAdvance('S')
        && line.MatchCharAndAdvance('R')) {
        mode.SetMode(AddressModes::STATUS_REGISTER);
        return true;
    }
    return false;
}

bool AssembleUSP(Line& line, AddressModeData& mode) {
    // USP
    if (line.MatchCharAndAdvance('U')
        && line.MatchCharAndAdvance('S')
        && line.MatchCharAndAdvance('P')) {
        mode.SetMode(AddressModes::USER_STACK_POINTER);
        return true;
    }
    return false;
}

bool AssembleAddressMode(Line& line, AddressModeData& mode) {
    if (line.MatchChar('A')) {
        // An
        return AssembleAddressRegisterDirect(line, mode);
    } else if (line.MatchChar('C')) {
        // CCR
        return AssembleCCR(line, mode);
    } else if (line.MatchChar('D')) {
        // Dn
        return AssembleDataRegisterDirect(line, mode);
    } else if (line.MatchChar('S')) {
        // SR
        return AssembleSR(line, mode);
    } else if (line.MatchChar('U')) {
        // USP
        return AssembleUSP(line, mode);
    } else if (line.MatchCharAndAdvance('(')) {
        // Potentially one of the following
        // (An), (An)+
        // (d16, An), (d8, An, Xn)
        // (d16, PC), (d8, PC, Xn)
        // (XXX).W, (XXX).L
        return AssembleIndirectOrAbsolute(line, mode);
    } else if (line.MatchCharAndAdvance('-')) {
        // -(An)
        if (line.MatchCharAndAdvance('(')) {
            return AssembleAddressRegisterIndirectWithPreDecrement(line, mode);
        }
    } else if (line.MatchCharAndAdvance('#')) {
        // #number
        return AssembleImmediate(line, mode);
    }
    return false;
}

bool AssembleLineEnd(Line& line) {
    return line.MatchEnd();
}

bool AssembleSourceMode(Line& line, InstructionData& data) {
    return AssembleAddressMode(line, data.GetSourceData());
}

bool AssembleDestinationMode(Line& line, InstructionData& data) {
    return AssembleAddressMode(line, data.GetDestinationData());
}

bool AssembleSourceAndDestinationModes(Line& line, InstructionData& data) {
    if (AssembleSourceMode(line, data)) {
        if (line.MatchCommaAndWhiteSpaceAndAdvance()) {
            return AssembleDestinationMode(line, data);
        }
    }
    return false;
}

bool AssembleNiladicInstruction(Line& line, InstructionData&) {
    return AssembleLineEnd(line);
}

bool AssembleMonadicInstruction(Line& line, InstructionData& data) {
    if (line.MatchWhiteSpaceAndAdvance()) {
        if (AssembleDestinationMode(line, data)) {
            return AssembleLineEnd(line);
        }
    }
    return false;
}

bool AssembleMonadicInstructionWithSize(Line& line, InstructionData& data) {
    OperandSizes size{};
    if (AssembleSize(line, size)) {
        data.SetSize(size);
        return AssembleMonadicInstruction(line, data);
    }
    return false;
}

bool AssembleDyadicInstruction(Line& line, InstructionData& data) {
    if (line.MatchWhiteSpaceAndAdvance()) {
        if (AssembleSourceAndDestinationModes(line, data)) {
            return AssembleLineEnd(line);
        }
    }
    return false;
}

bool AssembleDyadicInstructionWithSize(Line& line, InstructionData& data) {
    OperandSizes size{};
    if (AssembleSize(line, size)) {
        data.SetSize(size);
        return AssembleDyadicInstruction(line, data);
    }
    return false;
}

bool AssembleShiftRotateInstruction(Line& line, InstructionData& data) {
    OperandSizes size{};
    if (AssembleSize(line, size)) {
        data.SetSize(size);
        if (line.MatchWhiteSpaceAndAdvance()) {
            if (line.MatchChar('D') || line.MatchChar('#')) {
                return AssembleSourceAndDestinationModes(line, data);
            }
            return AssembleDestinationMode(line, data);
        }
    }
    return false;
}

bool AssembleBranchDisplacement(Line& line, int64_t& displacement) {
    if (line.MatchCharAndAdvance('*')) {
        if (line.MatchNumberPrefixOrDigit()) {
            return AssembleNumber(line, displacement);
        }
    }
    return false;
}

bool AssembleBranchCondition(Line& line, ConditionCodes code, InstructionData& data) {
    int64_t number;
    if (AssembleBranchDisplacement(line, number)) {
        auto& branch = data.GetBranchCondition();
        branch.SetCode(code);
        branch.SetDisplacement(number);
        return true;
    }
    return false;
}

bool AssembleDecrementBranchInstruction(Line& line, ConditionCodes code, InstructionData& data) {
    if (line.MatchWhiteSpaceAndAdvance()) {
        if (AssembleSourceMode(line, data)) {
            if (line.MatchCommaAndWhiteSpaceAndAdvance()) {
                if (AssembleBranchCondition(line, code, data)) {
                    return AssembleLineEnd(line);
                }
            }
        }
    }
    return false;
}

bool AssembleBranchInstruction(Line& line, ConditionCodes code, InstructionData& data) {
    OperandSizes size{};
    if (AssembleSize(line, size)) {
        data.SetSize(size);
        if (line.MatchWhiteSpaceAndAdvance()) {
            if (AssembleBranchCondition(line, code, data)) {
                return AssembleLineEnd(line);
            }
        }
    }
    return false;
}

bool AssembleRange(Line& line, int64_t start, RegisterList& list) {
    int64_t end;
    if (line.MatchCharAndAdvance('-')) {
        if (line.MatchChar('A')) {
            if (AssembleAddressRegister(line, end)) {
                end += 8u;
                list.Accumulate(start, end);
                return true;
            }
        } else if (line.MatchChar('D')) {
            if (AssembleDataRegister(line, end)) {
                list.Accumulate(start, end);
                return true;
            }
        }
    }
    return false;
}

bool AssembleAddressRegisterOrRange(Line& line, RegisterList& list) {
    int64_t start;
    if (AssembleAddressRegister(line, start)) {
        start += 8u;
        if (line.MatchChar('-')) {
            return AssembleRange(line, start, list);
        } else {
            list.Accumulate(start, start);
            return true;
        }
    }
    return false;
}

bool AssembleDataRegisterOrRange(Line& line, RegisterList& list) {
    int64_t start;
    if (AssembleDataRegister(line, start)) {
        if (line.MatchChar('-')) {
            return AssembleRange(line, start, list);
        } else {
            list.Accumulate(start, start);
            return true;
        }
    }
    return false;
}

bool AssembleRegisterOrRange(Line& line, RegisterList& list) {
    if (line.MatchChar('A')) {
        return AssembleAddressRegisterOrRange(line, list);
    } else if (line.MatchChar('D')) {
        return AssembleDataRegisterOrRange(line, list);
    }
    return false;
}

bool AssembleRegisterList(Line& line, RegisterList& list) {
    if (AssembleRegisterOrRange(line, list)) {
        while (line.MatchCharAndAdvance('/')) {
            if (!AssembleRegisterOrRange(line, list)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool AssembleMoveMultipleInstruction(Line& line, InstructionData& data) {
    OperandSizes size{};
    if (AssembleSize(line, size)) {
        data.SetSize(size);
        if (line.MatchWhiteSpaceAndAdvance()) {
            if (line.MatchChar('A') || line.MatchChar('D')) {
                if (AssembleRegisterList(line, data.GetRegisterList())) {
                    if (line.MatchCommaAndWhiteSpaceAndAdvance()) {
                        if (AssembleDestinationMode(line, data)) {
                            return AssembleLineEnd(line);
                        }
                    }
                }
            } else if (AssembleSourceMode(line, data)) {
                if (line.MatchCommaAndWhiteSpaceAndAdvance()) {
                    if (AssembleRegisterList(line, data.GetRegisterList())) {
                        return AssembleLineEnd(line);
                    }
                }
            }
        }
    }
    return false;
}

bool AssembleABCD(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::ABCD);
    data.SetSize(OperandSizes::BYTE);
    if (AssembleDyadicInstruction(line, data)) {
        return EmitABCD(data, emitter);
    }
    return false;
}

bool AssembleADDA(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::ADDA);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitADDA(data, emitter);
    }
    return false;
}

bool AssembleADDI(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::ADDI);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitADDI(data, emitter);
    }
    return false;
}

bool AssembleADDQ(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::ADDQ);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitADDQ(data, emitter);
    }
    return false;
}

bool AssembleADDX(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::ADDX);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitADDX(data, emitter);
    }
    return false;
}

bool AssembleADD(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::ADD);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitADD(data, emitter);
    }
    return false;
}

bool AssembleANDI(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleDyadicInstructionWithSize(line, data)) {
        const auto mode = data.GetDestinationData().GetMode();
        if (mode == AddressModes::CONDITION_CODE_REGISTER) {
            data.SetMnemonic(InstructionMnemonics::ANDI_CCR);
            return EmitANDI_CCR(data, emitter);
        } else if (mode == AddressModes::STATUS_REGISTER) {
            data.SetMnemonic(InstructionMnemonics::ANDI_SR);
            return EmitANDI_SR(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::ANDI);
            return EmitANDI(data, emitter);
        }
    }
    return false;
}

bool AssembleAND(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::AND);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitAND(data, emitter);
    }
    return false;
}

bool AssembleASL(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleShiftRotateInstruction(line, data)) {
        const auto mode = data.GetSourceData().GetMode();
        if (mode == AddressModes::UNKNOWN) {
            data.SetMnemonic(InstructionMnemonics::ASL_MEMORY);
            return EmitASL_Memory(data, emitter);
        } else if (mode == AddressModes::DATA_DIRECT) {
            data.SetMnemonic(InstructionMnemonics::ASL_REGISTER);
            return EmitASL_Register(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::ASL_IMMEDIATE);
            return EmitASL_Immediate(data, emitter);
        }
    }
    return false;
}

bool AssembleASR(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleShiftRotateInstruction(line, data)) {
        const auto mode = data.GetSourceData().GetMode();
        if (mode == AddressModes::UNKNOWN) {
            data.SetMnemonic(InstructionMnemonics::ASR_MEMORY);
            return EmitASR_Memory(data, emitter);
        } else if (mode == AddressModes::DATA_DIRECT) {
            data.SetMnemonic(InstructionMnemonics::ASR_REGISTER);
            return EmitASR_Register(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::ASR_IMMEDIATE);
            return EmitASR_Immediate(data, emitter);
        }
    }
    return false;
}

bool AssembleBcc(Line& line, ConditionCodes code, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::Bcc);
    if (AssembleBranchInstruction(line, code, data)) {
        return EmitBcc(data, emitter);
    }
    return false;
}

bool AssembleBCHG(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleDyadicInstructionWithSize(line, data)) {
        const auto destination = data.GetDestinationData().GetMode();
        const auto source = data.GetSourceData().GetMode();
        if (destination == AddressModes::DATA_DIRECT) {
            if (source == AddressModes::DATA_DIRECT) {
                data.SetMnemonic(InstructionMnemonics::BCHG_DYNAMIC_REGISTER);
                return EmitBCHG_Dynamic_Register(data, emitter);
            } else {
                data.SetMnemonic(InstructionMnemonics::BCHG_STATIC_REGISTER);
                return EmitBCHG_Static_Register(data, emitter);
            }
        } else if (source == AddressModes::DATA_DIRECT) {
            data.SetMnemonic(InstructionMnemonics::BCHG_DYNAMIC_MEMORY);
            return EmitBCHG_Dynamic_Memory(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::BCHG_STATIC_MEMORY);
            return EmitBCHG_Static_Memory(data, emitter);
        }
    }
    return false;
}

bool AssembleBCLR(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleDyadicInstructionWithSize(line, data)) {
        const auto destination = data.GetDestinationData().GetMode();
        const auto source = data.GetSourceData().GetMode();
        if (destination == AddressModes::DATA_DIRECT) {
            if (source == AddressModes::DATA_DIRECT) {
                data.SetMnemonic(InstructionMnemonics::BCLR_DYNAMIC_REGISTER);
                return EmitBCLR_Dynamic_Register(data, emitter);
            } else {
                data.SetMnemonic(InstructionMnemonics::BCLR_STATIC_REGISTER);
                return EmitBCLR_Static_Register(data, emitter);
            }
        } else if (source == AddressModes::DATA_DIRECT) {
            data.SetMnemonic(InstructionMnemonics::BCLR_DYNAMIC_MEMORY);
            return EmitBCLR_Dynamic_Memory(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::BCLR_STATIC_MEMORY);
            return EmitBCLR_Static_Memory(data, emitter);
        }
    }
    return false;
}

bool AssembleBRA(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::BRA);
    if (AssembleBranchInstruction(line, ConditionCodes::TRUE, data)) {
        return EmitBRA(data, emitter);
    }
    return false;
}

bool AssembleBSET(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleDyadicInstructionWithSize(line, data)) {
        const auto destination = data.GetDestinationData().GetMode();
        const auto source = data.GetSourceData().GetMode();
        if (destination == AddressModes::DATA_DIRECT) {
            if (source == AddressModes::DATA_DIRECT) {
                data.SetMnemonic(InstructionMnemonics::BSET_DYNAMIC_REGISTER);
                return EmitBSET_Dynamic_Register(data, emitter);
            } else {
                data.SetMnemonic(InstructionMnemonics::BSET_STATIC_REGISTER);
                return EmitBSET_Static_Register(data, emitter);
            }
        } else if (source == AddressModes::DATA_DIRECT) {
            data.SetMnemonic(InstructionMnemonics::BSET_DYNAMIC_MEMORY);
            return EmitBSET_Dynamic_Memory(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::BSET_STATIC_MEMORY);
            return EmitBSET_Static_Memory(data, emitter);
        }
    }
    return false;
}

bool AssembleBSR(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::BSR);
    if (AssembleBranchInstruction(line, ConditionCodes::FALSE, data)) {
        return EmitBSR(data, emitter);
    }
    return false;
}

bool AssembleBTST(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleDyadicInstructionWithSize(line, data)) {
        const auto destination = data.GetDestinationData().GetMode();
        const auto source = data.GetSourceData().GetMode();
        if (destination == AddressModes::DATA_DIRECT) {
            if (source == AddressModes::DATA_DIRECT) {
                data.SetMnemonic(InstructionMnemonics::BTST_DYNAMIC_REGISTER);
                return EmitBTST_Dynamic_Register(data, emitter);
            } else {
                data.SetMnemonic(InstructionMnemonics::BTST_STATIC_REGISTER);
                return EmitBTST_Static_Register(data, emitter);
            }
        } else if (source == AddressModes::DATA_DIRECT) {
            data.SetMnemonic(InstructionMnemonics::BTST_DYNAMIC_MEMORY);
            return EmitBTST_Dynamic_Memory(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::BTST_STATIC_MEMORY);
            return EmitBTST_Static_Memory(data, emitter);
        }
    }
    return false;
}

bool AssembleCHK(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::CHK);
    data.SetSize(OperandSizes::WORD);
    if (AssembleDyadicInstruction(line, data)) {
        return EmitCHK(data, emitter);
    }
    return false;
}

bool AssembleCLR(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::CLR);
    if (AssembleMonadicInstructionWithSize(line, data)) {
        return EmitCLR(data, emitter);
    }
    return false;
}

bool AssembleCMPA(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::CMPA);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitCMPA(data, emitter);
    }
    return false;
}

bool AssembleCMPI(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::CMPI);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitCMPI(data, emitter);
    }
    return false;
}

bool AssembleCMPM(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::CMPM);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitCMPM(data, emitter);
    }
    return false;
}

bool AssembleCMP(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::CMP);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitCMP(data, emitter);
    }
    return false;
}

bool AssembleDBcc(Line& line, ConditionCodes code, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::DBcc);
    data.SetSize(OperandSizes::WORD);
    if (AssembleDecrementBranchInstruction(line, code, data)) {
        return EmitDBcc(data, emitter);
    }
    return false;
}

bool AssembleDIVS(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::DIVS);
    data.SetSize(OperandSizes::WORD);
    if (AssembleDyadicInstruction(line, data)) {
        return EmitDIVS(data, emitter);
    }
    return false;
}

bool AssembleDIVU(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::DIVU);
    data.SetSize(OperandSizes::WORD);
    if (AssembleDyadicInstruction(line, data)) {
        return EmitDIVU(data, emitter);
    }
    return false;
}

bool AssembleEORI(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleDyadicInstructionWithSize(line, data)) {
        const auto mode = data.GetDestinationData().GetMode();
        if (mode == AddressModes::CONDITION_CODE_REGISTER) {
            data.SetMnemonic(InstructionMnemonics::EORI_CCR);
            return EmitEORI_CCR(data, emitter);
        } else if (mode == AddressModes::STATUS_REGISTER) {
            data.SetMnemonic(InstructionMnemonics::EORI_SR);
            return EmitEORI_SR(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::EORI);
            return EmitEORI(data, emitter);
        }
    }
    return false;
}

bool AssembleEOR(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::EOR);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitEOR(data, emitter);
    }
    return false;
}

bool AssembleEXG(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::EXG);
    data.SetSize(OperandSizes::LONG);
    if (AssembleDyadicInstruction(line, data)) {
        return EmitEXG(data, emitter);
    }
    return false;
}

bool AssembleEXT(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::EXT);
    if (AssembleMonadicInstructionWithSize(line, data)) {
        return EmitEXT(data, emitter);
    }
    return false;
}

bool AssembleILLEGAL(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::ILLEGAL);
    data.SetSize(OperandSizes::UNSIZED);
    if (AssembleNiladicInstruction(line, data)) {
        return EmitILLEGAL(data, emitter);
    }
    return false;
}

bool AssembleJMP(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::JMP);
    data.SetSize(OperandSizes::UNSIZED);
    if (AssembleMonadicInstruction(line, data)) {
        return EmitJMP(data, emitter);
    }
    return false;
}

bool AssembleJSR(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::JSR);
    data.SetSize(OperandSizes::UNSIZED);
    if (AssembleMonadicInstruction(line, data)) {
        return EmitJSR(data, emitter);
    }
    return false;
}

bool AssembleLEA(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::LEA);
    data.SetSize(OperandSizes::LONG);
    if (AssembleDyadicInstruction(line, data)) {
        return EmitLEA(data, emitter);
    }
    return false;
}

bool AssembleLINK(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::LINK);
    data.SetSize(OperandSizes::WORD);
    if (AssembleDyadicInstruction(line, data)) {
        return EmitLINK(data, emitter);
    }
    return false;
}

bool AssembleLSL(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleShiftRotateInstruction(line, data)) {
        const auto mode = data.GetSourceData().GetMode();
        if (mode == AddressModes::UNKNOWN) {
            data.SetMnemonic(InstructionMnemonics::LSL_MEMORY);
            return EmitLSL_Memory(data, emitter);
        } else if (mode == AddressModes::DATA_DIRECT) {
            data.SetMnemonic(InstructionMnemonics::LSL_REGISTER);
            return EmitLSL_Register(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::LSL_IMMEDIATE);
            return EmitLSL_Immediate(data, emitter);
        }
    }
    return false;
}

bool AssembleLSR(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleShiftRotateInstruction(line, data)) {
        const auto mode = data.GetSourceData().GetMode();
        if (mode == AddressModes::UNKNOWN) {
            data.SetMnemonic(InstructionMnemonics::LSR_MEMORY);
            return EmitLSR_Memory(data, emitter);
        } else if (mode == AddressModes::DATA_DIRECT) {
            data.SetMnemonic(InstructionMnemonics::LSR_REGISTER);
            return EmitLSR_Register(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::LSR_IMMEDIATE);
            return EmitLSR_Immediate(data, emitter);
        }
    }
    return false;
}

bool AssembleMOVEA(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::MOVEA);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitMOVEA(data, emitter);
    }
    return false;
}

bool AssembleMOVEM(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleMoveMultipleInstruction(line, data)) {
        auto source = data.GetSourceData().GetMode();
        if (source == AddressModes::UNKNOWN) {
            data.SetMnemonic(InstructionMnemonics::MOVEM_MEMORY);
            return EmitMOVEM_Memory(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::MOVEM_REGISTER);
            return EmitMOVEM_Register(data, emitter);
        }
    }
    return false;
}

bool AssembleMOVEP(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::MOVEP);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitMOVEP(data, emitter);
    }
    return false;
}

bool AssembleMOVEQ(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::MOVEQ);
    data.SetSize(OperandSizes::LONG);
    if (AssembleDyadicInstruction(line, data)) {
        return EmitMOVEQ(data, emitter);
    }
    return false;
}

bool AssembleMOVE(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleDyadicInstructionWithSize(line, data)) {
        const auto destination = data.GetDestinationData().GetMode();
        const auto source = data.GetSourceData().GetMode();
        if (source == AddressModes::USER_STACK_POINTER) {
            data.SetMnemonic(InstructionMnemonics::MOVE_USP_REGISTER);
            return EmitMOVE_USP_Register(data, emitter);
        } else if (destination == AddressModes::USER_STACK_POINTER) {
            data.SetMnemonic(InstructionMnemonics::MOVE_USP_USP);
            return EmitMOVE_USP_USP(data, emitter);
        } else if (source == AddressModes::STATUS_REGISTER) {
            data.SetMnemonic(InstructionMnemonics::MOVE_SR_MEMORY);
            return EmitMOVE_SR_Memory(data, emitter);
        } else if (destination == AddressModes::STATUS_REGISTER) {
            data.SetMnemonic(InstructionMnemonics::MOVE_SR_SR);
            return EmitMOVE_SR_SR(data, emitter);
        } else if (destination == AddressModes::CONDITION_CODE_REGISTER) {
            data.SetMnemonic(InstructionMnemonics::MOVE_CCR);
            return EmitMOVE_CCR(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::MOVE);
            return EmitMOVE(data, emitter);
        }
    }
    return false;
}

bool AssembleMULS(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::MULS);
    data.SetSize(OperandSizes::WORD);
    if (AssembleDyadicInstruction(line, data)) {
        return EmitMULS(data, emitter);
    }
    return false;
}

bool AssembleMULU(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::MULU);
    data.SetSize(OperandSizes::WORD);
    if (AssembleDyadicInstruction(line, data)) {
        return EmitMULU(data, emitter);
    }
    return false;
}

bool AssembleNBCD(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::NBCD);
    data.SetSize(OperandSizes::BYTE);
    if (AssembleMonadicInstruction(line, data)) {
        return EmitNBCD(data, emitter);
    }
    return false;
}

bool AssembleNEGX(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::NEGX);
    if (AssembleMonadicInstructionWithSize(line, data)) {
        return EmitNEGX(data, emitter);
    }
    return false;
}

bool AssembleNEG(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::NEG);
    if (AssembleMonadicInstructionWithSize(line, data)) {
        return EmitNEG(data, emitter);
    }
    return false;
}

bool AssembleNOP(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::NOP);
    data.SetSize(OperandSizes::UNSIZED);
    if (AssembleNiladicInstruction(line, data)) {
        return EmitNOP(data, emitter);
    }
    return false;
}

bool AssembleNOT(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::NOT);
    if (AssembleMonadicInstructionWithSize(line, data)) {
        return EmitNOT(data, emitter);
    }
    return false;
}

bool AssembleORI(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleDyadicInstructionWithSize(line, data)) {
        auto mode = data.GetDestinationData().GetMode();
        if (mode == AddressModes::CONDITION_CODE_REGISTER) {
            data.SetMnemonic(InstructionMnemonics::ORI_CCR);
            return EmitORI_CCR(data, emitter);
        } else if (mode == AddressModes::STATUS_REGISTER) {
            data.SetMnemonic(InstructionMnemonics::ORI_SR);
            return EmitORI_SR(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::ORI);
            return EmitORI(data, emitter);
        }
    }
    return false;
}

bool AssembleOR(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::OR);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitOR(data, emitter);
    }
    return false;
}

bool AssemblePEA(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::PEA);
    data.SetSize(OperandSizes::LONG);
    if (AssembleMonadicInstruction(line, data)) {
        return EmitPEA(data, emitter);
    }
    return false;
}

bool AssembleRESET(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::RESET);
    data.SetSize(OperandSizes::UNSIZED);
    if (AssembleNiladicInstruction(line, data)) {
        return EmitRESET(data, emitter);
    }
    return false;
}

bool AssembleROL(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleShiftRotateInstruction(line, data)) {
        const auto mode = data.GetSourceData().GetMode();
        if (mode == AddressModes::UNKNOWN) {
            data.SetMnemonic(InstructionMnemonics::ROL_MEMORY);
            return EmitROL_Memory(data, emitter);
        } else if (mode == AddressModes::DATA_DIRECT) {
            data.SetMnemonic(InstructionMnemonics::ROL_REGISTER);
            return EmitROL_Register(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::ROL_IMMEDIATE);
            return EmitROL_Immediate(data, emitter);
        }
    }
    return false;
}

bool AssembleROR(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleShiftRotateInstruction(line, data)) {
        const auto mode = data.GetSourceData().GetMode();
        if (mode == AddressModes::UNKNOWN) {
            data.SetMnemonic(InstructionMnemonics::ROR_MEMORY);
            return EmitROR_Memory(data, emitter);
        } else if (mode == AddressModes::DATA_DIRECT) {
            data.SetMnemonic(InstructionMnemonics::ROR_REGISTER);
            return EmitROR_Register(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::ROR_IMMEDIATE);
            return EmitROR_Immediate(data, emitter);
        }
    }
    return false;
}

bool AssembleROXL(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleShiftRotateInstruction(line, data)) {
        const auto mode = data.GetSourceData().GetMode();
        if (mode == AddressModes::UNKNOWN) {
            data.SetMnemonic(InstructionMnemonics::ROXL_MEMORY);
            return EmitROXL_Memory(data, emitter);
        } else if (mode == AddressModes::DATA_DIRECT) {
            data.SetMnemonic(InstructionMnemonics::ROXL_REGISTER);
            return EmitROXL_Register(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::ROXL_IMMEDIATE);
            return EmitROXL_Immediate(data, emitter);
        }
    }
    return false;
}

bool AssembleROXR(Line& line, Emitter& emitter) {
    InstructionData data;
    if (AssembleShiftRotateInstruction(line, data)) {
        const auto mode = data.GetSourceData().GetMode();
        if (mode == AddressModes::UNKNOWN) {
            data.SetMnemonic(InstructionMnemonics::ROXR_MEMORY);
            return EmitROXR_Memory(data, emitter);
        } else if (mode == AddressModes::DATA_DIRECT) {
            data.SetMnemonic(InstructionMnemonics::ROXR_REGISTER);
            return EmitROXR_Register(data, emitter);
        } else {
            data.SetMnemonic(InstructionMnemonics::ROXR_IMMEDIATE);
            return EmitROXR_Immediate(data, emitter);
        }
    }
    return false;
}

bool AssembleRTE(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::RTE);
    data.SetSize(OperandSizes::UNSIZED);
    if (AssembleNiladicInstruction(line, data)) {
        return EmitRTE(data, emitter);
    }
    return false;
}

bool AssembleRTR(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::RTR);
    data.SetSize(OperandSizes::UNSIZED);
    if (AssembleNiladicInstruction(line, data)) {
        return EmitRTR(data, emitter);
    }
    return false;
}

bool AssembleRTS(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::RTS);
    data.SetSize(OperandSizes::UNSIZED);
    if (AssembleNiladicInstruction(line, data)) {
        return EmitRTS(data, emitter);
    }
    return false;
}

bool AssembleSBCD(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::SBCD);
    data.SetSize(OperandSizes::BYTE);
    if (AssembleDyadicInstruction(line, data)) {
        return EmitSBCD(data, emitter);
    }
    return false;
}

bool AssembleScc(Line& line, ConditionCodes code, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::Scc);
    data.SetSize(OperandSizes::BYTE);
    if (AssembleMonadicInstruction(line, data)) {
        auto& branch = data.GetBranchCondition();
        branch.SetCode(code);
        return EmitScc(data, emitter);
    }
    return false;
}

bool AssembleSTOP(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::STOP);
    data.SetSize(OperandSizes::UNSIZED);
    if (AssembleMonadicInstruction(line, data)) {
        return EmitSTOP(data, emitter);
    }
    return false;
}

bool AssembleSUBA(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::SUBA);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitSUBA(data, emitter);
    }
    return false;
}

bool AssembleSUBI(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::SUBI);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitSUBI(data, emitter);
    }
    return false;
}

bool AssembleSUBQ(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::SUBQ);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitSUBQ(data, emitter);
    }
    return false;
}

bool AssembleSUBX(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::SUBX);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitSUBX(data, emitter);
    }
    return false;
}

bool AssembleSUB(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::SUB);
    if (AssembleDyadicInstructionWithSize(line, data)) {
        return EmitSUB(data, emitter);
    }
    return false;
}

bool AssembleSWAP(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::SWAP);
    data.SetSize(OperandSizes::WORD);
    if (AssembleMonadicInstruction(line, data)) {
        return EmitSWAP(data, emitter);
    }
    return false;
}

bool AssembleTAS(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::TAS);
    data.SetSize(OperandSizes::BYTE);
    if (AssembleMonadicInstruction(line, data)) {
        return EmitTAS(data, emitter);
    }
    return false;
}

bool AssembleTRAPV(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::TRAPV);
    data.SetSize(OperandSizes::UNSIZED);
    if (AssembleNiladicInstruction(line, data)) {
        return EmitTRAPV(data, emitter);
    }
    return false;
}

bool AssembleTRAP(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::TRAP);
    data.SetSize(OperandSizes::UNSIZED);
    if (AssembleMonadicInstruction(line, data)) {
        return EmitTRAP(data, emitter);
    }
    return false;
}

bool AssembleTST(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::TST);
    if (AssembleMonadicInstructionWithSize(line, data)) {
        return EmitTST(data, emitter);
    }
    return false;
}

bool AssembleUNLK(Line& line, Emitter& emitter) {
    InstructionData data;
    data.SetMnemonic(InstructionMnemonics::UNLK);
    data.SetSize(OperandSizes::UNSIZED);
    if (AssembleMonadicInstruction(line, data)) {
        return EmitUNLK(data, emitter);
    }
    return false;
}

bool AssembleInstructionA(Line& line, Emitter& emitter) {
    if (line.MatchCharAndAdvance('B')) {
        if (line.MatchCharAndAdvance('C')
            && line.MatchCharAndAdvance('D')) {
            return AssembleABCD(line, emitter);
        }
    } else if (line.MatchCharAndAdvance('D')) {
        if (line.MatchCharAndAdvance('D')) {
            if (line.MatchCharAndAdvance('A')) {
                return AssembleADDA(line, emitter);
            } else if (line.MatchCharAndAdvance('I')) {
                return AssembleADDI(line, emitter);
            } else if (line.MatchCharAndAdvance('Q')) {
                return AssembleADDQ(line, emitter);
            } else if (line.MatchCharAndAdvance('X')) {
                return AssembleADDX(line, emitter);
            } else {
                return AssembleADD(line, emitter);
            }
        }
    } else if (line.MatchCharAndAdvance('N')) {
        if (line.MatchCharAndAdvance('D')) {
            if (line.MatchCharAndAdvance('I')) {
                return AssembleANDI(line, emitter);
            } else {
                return AssembleAND(line, emitter);
            }
        }
    } else if (line.MatchCharAndAdvance('S')) {
        if (line.MatchCharAndAdvance('L')) {
            return AssembleASL(line, emitter);
        } else if (line.MatchCharAndAdvance('R')) {
            return AssembleASR(line, emitter);
        }
    }
    return false;
}

bool AssembleInstructionB(Line& line, Emitter& emitter) {
    if (line.MatchCharAndAdvance('C')) {
        if (line.MatchCharAndAdvance('C')) {
            return AssembleBcc(line, ConditionCodes::CC, emitter);
        } else if (line.MatchCharAndAdvance('H')
                   && line.MatchCharAndAdvance('G')) {
            return AssembleBCHG(line, emitter);
        } else if (line.MatchCharAndAdvance('L')
                   && line.MatchCharAndAdvance('R')) {
            return AssembleBCLR(line, emitter);
        } else if (line.MatchCharAndAdvance('S')) {
            return AssembleBcc(line, ConditionCodes::CS, emitter);
        }
    } else if (line.MatchCharAndAdvance('E')) {
        if (line.MatchCharAndAdvance('Q')) {
            return AssembleBcc(line, ConditionCodes::EQ, emitter);
        }
    } else if (line.MatchCharAndAdvance('G')) {
        if (line.MatchCharAndAdvance('E')) {
            return AssembleBcc(line, ConditionCodes::GE, emitter);
        } else if (line.MatchCharAndAdvance('T')) {
            return AssembleBcc(line, ConditionCodes::GT, emitter);
        }
    } else if (line.MatchCharAndAdvance('H')) {
        if (line.MatchCharAndAdvance('I')) {
            return AssembleBcc(line, ConditionCodes::HI, emitter);
        }
    } else if (line.MatchCharAndAdvance('L')) {
        if (line.MatchCharAndAdvance('E')) {
            return AssembleBcc(line, ConditionCodes::LE, emitter);
        } else if (line.MatchCharAndAdvance('S')) {
            return AssembleBcc(line, ConditionCodes::LS, emitter);
        } else if (line.MatchCharAndAdvance('T')) {
            return AssembleBcc(line, ConditionCodes::LT, emitter);
        }
    } else if (line.MatchCharAndAdvance('M')) {
        if (line.MatchCharAndAdvance('I')) {
            return AssembleBcc(line, ConditionCodes::MI, emitter);
        }
    } else if (line.MatchCharAndAdvance('N')) {
        if (line.MatchCharAndAdvance('E')) {
            return AssembleBcc(line, ConditionCodes::NE, emitter);
        }
    } else if (line.MatchCharAndAdvance('P')) {
        if (line.MatchCharAndAdvance('L')) {
            return AssembleBcc(line, ConditionCodes::PL, emitter);
        }
    } else if (line.MatchCharAndAdvance('R')) {
        if (line.MatchCharAndAdvance('A')) {
            return AssembleBRA(line, emitter);
        }
    } else if (line.MatchCharAndAdvance('S')) {
        if (line.MatchCharAndAdvance('E')) {
            if (line.MatchCharAndAdvance('T')) {
                return AssembleBSET(line, emitter);
            }
        } else if (line.MatchCharAndAdvance('R')) {
            return AssembleBSR(line, emitter);
        }
    } else if (line.MatchCharAndAdvance('T')) {
        if (line.MatchCharAndAdvance('S')
            && line.MatchCharAndAdvance('T')) {
            return AssembleBTST(line, emitter);
        }
    } else if (line.MatchCharAndAdvance('V')) {
        if (line.MatchCharAndAdvance('C')) {
            return AssembleBcc(line, ConditionCodes::VC, emitter);
        } else if (line.MatchCharAndAdvance('S')) {
            return AssembleBcc(line, ConditionCodes::VS, emitter);
        }
    }
    return false;
}

bool AssembleInstructionC(Line& line, Emitter& emitter) {
    if (line.MatchCharAndAdvance('H')) {
        if (line.MatchCharAndAdvance('K')) {
            return AssembleCHK(line, emitter);
        }
    } else if (line.MatchCharAndAdvance('L')) {
        if (line.MatchCharAndAdvance('R')) {
            return AssembleCLR(line, emitter);
        }
    } else if (line.MatchCharAndAdvance('M')) {
        if (line.MatchCharAndAdvance('P')) {
            if (line.MatchCharAndAdvance('A')) {
                return AssembleCMPA(line, emitter);
            } else if (line.MatchCharAndAdvance('I')) {
                return AssembleCMPI(line, emitter);
            } else if (line.MatchCharAndAdvance('M')) {
                return AssembleCMPM(line, emitter);
            } else {
                return AssembleCMP(line, emitter);
            }
        }
    }
    return false;
}

bool AssembleInstructionD(Line& line, Emitter& emitter) {
    if (line.MatchCharAndAdvance('B')) {
        if (line.MatchCharAndAdvance('C')) {
            if (line.MatchCharAndAdvance('C')) {
                return AssembleDBcc(line, ConditionCodes::CC, emitter);
            } else if (line.MatchCharAndAdvance('S')) {
                return AssembleDBcc(line, ConditionCodes::CS, emitter);
            }
        } else if (line.MatchCharAndAdvance('E')) {
            if (line.MatchCharAndAdvance('Q')) {
                return AssembleDBcc(line, ConditionCodes::EQ, emitter);
            }
        } else if (line.MatchCharAndAdvance('F')) {
            return AssembleDBcc(line, ConditionCodes::FALSE, emitter);
        } else if (line.MatchCharAndAdvance('G')) {
            if (line.MatchCharAndAdvance('E')) {
                return AssembleDBcc(line, ConditionCodes::GE, emitter);
            } else if (line.MatchCharAndAdvance('T')) {
                return AssembleDBcc(line, ConditionCodes::GT, emitter);
            }
        } else if (line.MatchCharAndAdvance('H')) {
            if (line.MatchCharAndAdvance('I')) {
                return AssembleDBcc(line, ConditionCodes::HI, emitter);
            }
        } else if (line.MatchCharAndAdvance('L')) {
            if (line.MatchCharAndAdvance('E')) {
                return AssembleDBcc(line, ConditionCodes::LE, emitter);
            } else if (line.MatchCharAndAdvance('S')) {
                return AssembleDBcc(line, ConditionCodes::LS, emitter);
            } else if (line.MatchCharAndAdvance('T')) {
                return AssembleDBcc(line, ConditionCodes::LT, emitter);
            }
        } else if (line.MatchCharAndAdvance('M')) {
            if (line.MatchCharAndAdvance('I')) {
                return AssembleDBcc(line, ConditionCodes::MI, emitter);
            }
        } else if (line.MatchCharAndAdvance('N')) {
            if (line.MatchCharAndAdvance('E')) {
                return AssembleDBcc(line, ConditionCodes::NE, emitter);
            }
        } else if (line.MatchCharAndAdvance('P')) {
            if (line.MatchCharAndAdvance('L')) {
                return AssembleDBcc(line, ConditionCodes::PL, emitter);
            }
        } else if (line.MatchCharAndAdvance('R')) {
            if (line.MatchCharAndAdvance('A')) {
                return AssembleDBcc(line, ConditionCodes::FALSE, emitter);
            }
        } else if (line.MatchCharAndAdvance('T')) {
            return AssembleDBcc(line, ConditionCodes::TRUE, emitter);
        } else if (line.MatchCharAndAdvance('V')) {
            if (line.MatchCharAndAdvance('C')) {
                return AssembleDBcc(line, ConditionCodes::VC, emitter);
            } else if (line.MatchCharAndAdvance('S')) {
                return AssembleDBcc(line, ConditionCodes::VS, emitter);
            }
        }
    } else if (line.MatchCharAndAdvance('I')) {
        if (line.MatchCharAndAdvance('V')) {
            if (line.MatchCharAndAdvance('S')) {
                return AssembleDIVS(line, emitter);
            } else if (line.MatchCharAndAdvance('U')) {
                return AssembleDIVU(line, emitter);
            }
        }
    }
    return false;
}

bool AssembleInstructionE(Line& line, Emitter& emitter) {
    if (line.MatchCharAndAdvance('O')) {
        if (line.MatchCharAndAdvance('R')) {
            if (line.MatchCharAndAdvance('I')) {
                return AssembleEORI(line, emitter);
            } else {
                return AssembleEOR(line, emitter);
            }
        }

    } else if (line.MatchCharAndAdvance('X')) {
        if (line.MatchCharAndAdvance('G')) {
            return AssembleEXG(line, emitter);
        } else if (line.MatchCharAndAdvance('T')) {
            return AssembleEXT(line, emitter);
        }
    }
    return false;
}

bool AssembleInstructionI(Line& line, Emitter& emitter) {
    if (line.MatchCharAndAdvance('L')
        && line.MatchCharAndAdvance('L')
        && line.MatchCharAndAdvance('E')
        && line.MatchCharAndAdvance('G')
        && line.MatchCharAndAdvance('A')
        && line.MatchCharAndAdvance('L')) {
        return AssembleILLEGAL(line, emitter);
    }
    return false;
}

bool AssembleInstructionJ(Line& line, Emitter& emitter) {
    if (line.MatchCharAndAdvance('M')) {
        if (line.MatchCharAndAdvance('P')) {
            return AssembleJMP(line, emitter);
        }
    } else if (line.MatchCharAndAdvance('S')) {
        if (line.MatchCharAndAdvance('R')) {
            return AssembleJSR(line, emitter);
        }
    }
    return false;
}

bool AssembleInstructionL(Line& line, Emitter& emitter) {
    if (line.MatchCharAndAdvance('E')) {
        if (line.MatchCharAndAdvance('A')) {
            return AssembleLEA(line, emitter);
        }
    } else if (line.MatchCharAndAdvance('I')) {
        if (line.MatchCharAndAdvance('N')
            && line.MatchCharAndAdvance('K')) {
            return AssembleLINK(line, emitter);
        }
    } else if (line.MatchCharAndAdvance('S')) {
        if (line.MatchCharAndAdvance('L')) {
            return AssembleLSL(line, emitter);
        } else if (line.MatchCharAndAdvance('R')) {
            return AssembleLSR(line, emitter);
        }
    }
    return false;
}

bool AssembleInstructionM(Line& line, Emitter& emitter) {
    if (line.MatchCharAndAdvance('O')) {
        if (line.MatchCharAndAdvance('V')
            && line.MatchCharAndAdvance('E')) {
            if (line.MatchCharAndAdvance('A')) {
                return AssembleMOVEA(line, emitter);
            } else if (line.MatchCharAndAdvance('M')) {
                return AssembleMOVEM(line, emitter);
            } else if (line.MatchCharAndAdvance('P')) {
                return AssembleMOVEP(line, emitter);
            } else if (line.MatchCharAndAdvance('Q')) {
                return AssembleMOVEQ(line, emitter);
            } else {
                return AssembleMOVE(line, emitter);
            }
        }
    } else if (line.MatchCharAndAdvance('U')) {
        if (line.MatchCharAndAdvance('L')) {
            if (line.MatchCharAndAdvance('S')) {
                return AssembleMULS(line, emitter);
            } else if (line.MatchCharAndAdvance('U')) {
                return AssembleMULU(line, emitter);
            }
        }
    }
    return false;
}

bool AssembleInstructionN(Line& line, Emitter& emitter) {
    if (line.MatchCharAndAdvance('B')) {
        if (line.MatchCharAndAdvance('C')
            && line.MatchCharAndAdvance('D')) {
            return AssembleNBCD(line, emitter);
        }
    } else if (line.MatchCharAndAdvance('E')) {
        if (line.MatchCharAndAdvance('G')) {
            if (line.MatchCharAndAdvance('X')) {
                return AssembleNEGX(line, emitter);
            } else {
                return AssembleNEG(line, emitter);
            }
        }
    } else if (line.MatchCharAndAdvance('O')) {
        if (line.MatchCharAndAdvance('P')) {
            return AssembleNOP(line, emitter);
        } else if (line.MatchCharAndAdvance('T')) {
            return AssembleNOT(line, emitter);
        }
    }
    return false;
}

bool AssembleInstructionO(Line& line, Emitter& emitter) {
    if (line.MatchCharAndAdvance('R')) {
        if (line.MatchCharAndAdvance('I')) {
            return AssembleORI(line, emitter);
        } else {
            return AssembleOR(line, emitter);
        }
    }
    return false;
}

bool AssembleInstructionP(Line& line, Emitter& emitter) {
    if (line.MatchCharAndAdvance('E')
        && line.MatchCharAndAdvance('A')) {
        return AssemblePEA(line, emitter);
    }
    return false;
}

bool AssembleInstructionR(Line& line, Emitter& emitter) {
    if (line.MatchCharAndAdvance('E')) {
        if (line.MatchCharAndAdvance('S')
            && line.MatchCharAndAdvance('E')
            && line.MatchCharAndAdvance('T')) {
            return AssembleRESET(line, emitter);
        }
    } else if (line.MatchCharAndAdvance('O')) {
        if (line.MatchCharAndAdvance('L')) {
            return AssembleROL(line, emitter);
        } else if (line.MatchCharAndAdvance('R')) {
            return AssembleROR(line, emitter);
        } else if (line.MatchCharAndAdvance('X')) {
            if (line.MatchCharAndAdvance('L')) {
                return AssembleROXL(line, emitter);
            } else if (line.MatchCharAndAdvance('R')) {
                return AssembleROXR(line, emitter);
            }
        }
    } else if (line.MatchCharAndAdvance('T')) {
        if (line.MatchCharAndAdvance('E')) {
            return AssembleRTE(line, emitter);
        } else if (line.MatchCharAndAdvance('R')) {
            return AssembleRTR(line, emitter);
        } else if (line.MatchCharAndAdvance('S')) {
            return AssembleRTS(line, emitter);
        }
    }
    return false;
}

bool AssembleInstructionS(Line& line, Emitter& emitter) {
    if (line.MatchCharAndAdvance('B')) {
        if (line.MatchCharAndAdvance('C')
            && line.MatchCharAndAdvance('D')) {
            return AssembleSBCD(line, emitter);
        }
    } else if (line.MatchCharAndAdvance('C')) {
        if (line.MatchCharAndAdvance('C')) {
            return AssembleScc(line, ConditionCodes::CC, emitter);
        } else if (line.MatchCharAndAdvance('S')) {
            return AssembleScc(line, ConditionCodes::CS, emitter);
        }
    } else if (line.MatchCharAndAdvance('E')) {
        if (line.MatchCharAndAdvance('Q')) {
            return AssembleScc(line, ConditionCodes::EQ, emitter);
        }
    } else if (line.MatchCharAndAdvance('F')) {
        return AssembleScc(line, ConditionCodes::FALSE, emitter);
    } else if (line.MatchCharAndAdvance('G')) {
        if (line.MatchCharAndAdvance('E')) {
            return AssembleScc(line, ConditionCodes::GE, emitter);
        } else if (line.MatchCharAndAdvance('T')) {
            return AssembleScc(line, ConditionCodes::GT, emitter);
        }
    } else if (line.MatchCharAndAdvance('H')) {
        if (line.MatchCharAndAdvance('I')) {
            return AssembleScc(line, ConditionCodes::HI, emitter);
        }
    } else if (line.MatchCharAndAdvance('L')) {
        if (line.MatchCharAndAdvance('E')) {
            return AssembleScc(line, ConditionCodes::LE, emitter);
        } else if (line.MatchCharAndAdvance('S')) {
            return AssembleScc(line, ConditionCodes::LS, emitter);
        } else if (line.MatchCharAndAdvance('T')) {
            return AssembleScc(line, ConditionCodes::LT, emitter);
        }
    } else if (line.MatchCharAndAdvance('M')) {
        if (line.MatchCharAndAdvance('I')) {
            return AssembleScc(line, ConditionCodes::MI, emitter);
        }
    } else if (line.MatchCharAndAdvance('N')) {
        if (line.MatchCharAndAdvance('E')) {
            return AssembleScc(line, ConditionCodes::NE, emitter);
        }
    } else if (line.MatchCharAndAdvance('P')) {
        if (line.MatchCharAndAdvance('L')) {
            return AssembleScc(line, ConditionCodes::PL, emitter);
        }
    } else if (line.MatchCharAndAdvance('T')) {
        if (line.MatchCharAndAdvance('O')) {
            if (line.MatchCharAndAdvance('P')) {
                return AssembleSTOP(line, emitter);
            }
        } else {
            return AssembleScc(line, ConditionCodes::TRUE, emitter);
        }
    } else if (line.MatchCharAndAdvance('U')) {
        if (line.MatchCharAndAdvance('B')) {
            if (line.MatchCharAndAdvance('A')) {
                return AssembleSUBA(line, emitter);
            } else if (line.MatchCharAndAdvance('I')) {
                return AssembleSUBI(line, emitter);
            } else if (line.MatchCharAndAdvance('Q')) {
                return AssembleSUBQ(line, emitter);
            } else if (line.MatchCharAndAdvance('X')) {
                return AssembleSUBX(line, emitter);
            } else {
                return AssembleSUB(line, emitter);
            }
        }
    } else if (line.MatchCharAndAdvance('V')) {
        if (line.MatchCharAndAdvance('C')) {
            return AssembleScc(line, ConditionCodes::VC, emitter);
        } else if (line.MatchCharAndAdvance('S')) {
            return AssembleScc(line, ConditionCodes::VS, emitter);
        }
    } else if (line.MatchCharAndAdvance('W')) {
        if (line.MatchCharAndAdvance('A')
            && line.MatchCharAndAdvance('P')) {
            return AssembleSWAP(line, emitter);
        }
    }
    return false;
}

bool AssembleInstructionT(Line& line, Emitter& emitter) {
    if (line.MatchCharAndAdvance('A')) {
        if (line.MatchCharAndAdvance('S')) {
            return AssembleTAS(line, emitter);
        }
    } else if (line.MatchCharAndAdvance('R')) {
        if (line.MatchCharAndAdvance('A')
            && line.MatchCharAndAdvance('P')) {
            if (line.MatchCharAndAdvance('V')) {
                return AssembleTRAPV(line, emitter);
            } else {
                return AssembleTRAP(line, emitter);
            }
        }
    } else if (line.MatchCharAndAdvance('S')) {
        if (line.MatchCharAndAdvance('T')) {
            return AssembleTST(line, emitter);
        }
    }
    return false;
}

bool AssembleInstructionU(Line& line, Emitter& emitter) {
    if (line.MatchCharAndAdvance('N')
        && line.MatchCharAndAdvance('L')
        && line.MatchCharAndAdvance('K')) {
        return AssembleUNLK(line, emitter);
    }
    return false;
}

bool AssembleInstruction(Line& line, Emitter emitter) {
    if (line.MatchCharAndAdvance('A')) {
        return AssembleInstructionA(line, emitter);
    } else if (line.MatchCharAndAdvance('B')) {
        return AssembleInstructionB(line, emitter);
    } else if (line.MatchCharAndAdvance('C')) {
        return AssembleInstructionC(line, emitter);
    } else if (line.MatchCharAndAdvance('D')) {
        return AssembleInstructionD(line, emitter);
    } else if (line.MatchCharAndAdvance('E')) {
        return AssembleInstructionE(line, emitter);
    } else if (line.MatchCharAndAdvance('I')) {
        return AssembleInstructionI(line, emitter);
    } else if (line.MatchCharAndAdvance('J')) {
        return AssembleInstructionJ(line, emitter);
    } else if (line.MatchCharAndAdvance('L')) {
        return AssembleInstructionL(line, emitter);
    } else if (line.MatchCharAndAdvance('M')) {
        return AssembleInstructionM(line, emitter);
    } else if (line.MatchCharAndAdvance('N')) {
        return AssembleInstructionN(line, emitter);
    } else if (line.MatchCharAndAdvance('O')) {
        return AssembleInstructionO(line, emitter);
    } else if (line.MatchCharAndAdvance('P')) {
        return AssembleInstructionP(line, emitter);
    } else if (line.MatchCharAndAdvance('R')) {
        return AssembleInstructionR(line, emitter);
    } else if (line.MatchCharAndAdvance('S')) {
        return AssembleInstructionS(line, emitter);
    } else if (line.MatchCharAndAdvance('T')) {
        return AssembleInstructionT(line, emitter);
    } else if (line.MatchCharAndAdvance('U')) {
        return AssembleInstructionU(line, emitter);
    }
    return false;
}

}

namespace rbrown::m68000 {
bool Assemble(const std::string& line, Instruction& instruction) {
    Line sourceLine(line);
    auto emitter = [&instruction](uint16_t v) {
        instruction.AppendWord(v);
    };
    return AssembleInstruction(sourceLine, emitter);
}
}