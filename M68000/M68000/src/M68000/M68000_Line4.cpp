#include "M68000/M68000.h"
#include "M68000/M68000_Opcode.h"
#include "M68000/M68000_EffectiveAddress.h"
#include "M68000/M68000_Operations.h"

using namespace rbrown::m68000;

auto M68000::ExecuteLine4(uint32_t opcode) -> void {
    switch (OpcodeModeX(opcode)) {
        case 0u: return ExecuteSingleOperationByte(opcode);
        case 1u: return ExecuteSingleOperationWord(opcode);
        case 2u: return ExecuteSingleOperationLong(opcode);
        case 3u: return ExecuteSingleOperationMove(opcode);
        case 6u: return ExecuteChk(opcode);
        case 7u: return ExecuteLea(opcode);
        [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteSingleOperationByte(uint32_t opcode) -> void {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return ExecuteNegx<Byte>(opcode);
        case 1u: return ExecuteClr<Byte>(opcode);
        case 2u: return ExecuteNeg<Byte>(opcode);
        case 3u: return ExecuteNot<Byte>(opcode);
        case 4u: return ExecuteNbcd<Byte>(opcode);
        case 5u: return ExecuteTst<Byte>(opcode);
        [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteSingleOperationWord(uint32_t opcode) -> void {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return ExecuteNegx<Word>(opcode);
        case 1u: return ExecuteClr<Word>(opcode);
        case 2u: return ExecuteNeg<Word>(opcode);
        case 3u: return ExecuteNot<Word>(opcode);
        case 4u: return ExecutePea(opcode);
        case 5u: return ExecuteTst<Word>(opcode);
        case 7u: return ExecuteSingleOperationMisc(opcode);
        [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteSingleOperationLong(uint32_t opcode) -> void {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return ExecuteNegx<Long>(opcode);
        case 1u: return ExecuteClr<Long>(opcode);
        case 2u: return ExecuteNeg<Long>(opcode);
        case 3u: return ExecuteNot<Long>(opcode);
        case 4u: return ExecuteMovemEffectiveAddress<Word>(opcode);
        case 5u: return ExecuteTst<Long>(opcode);
        case 6u: return ExecuteMovemRegister<Word>(opcode);
        case 7u: return ExecuteJsr(opcode);
        [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteSingleOperationMove(uint32_t opcode) -> void {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return ExecuteMoveFromSR(opcode);
        case 2u: return ExecuteMoveToCCR(opcode);
        case 3u: return ExecuteMoveToSR(opcode);
        case 4u: return ExecuteMovemEffectiveAddress<Long>(opcode);
        case 5u: return ExecuteTas(opcode);
        case 6u: return ExecuteMovemRegister<Long>(opcode);
        case 7u: return ExecuteJmp(opcode);
        [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteNegx(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteNegxDataRegister<T>(opcode);
        case 2u: return ExecuteNegxEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteNegxEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteNegxEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteNegxEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteNegxEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteNegxEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteNegxEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteClr(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteClrDataRegister<T>(opcode);
        case 2u: return ExecuteClrEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteClrEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteClrEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteClrEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteClrEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteClrEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteClrEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteNeg(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteNegDataRegister<T>(opcode);
        case 2u: return ExecuteNegEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteNegEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteNegEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteNegEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteNegEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteNegEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteNegEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteNot(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteNotDataRegister<T>(opcode);
        case 2u: return ExecuteNotEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteNotEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteNotEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteNotEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteNotEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteNotEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteNotEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteNbcd(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteNbcdDataRegister<T>(opcode);
        case 2u: return ExecuteNbcdEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteNbcdEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteNbcdEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteNbcdEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteNbcdEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteNbcdEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteNbcdEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteTst(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteTstDataRegister<T>(opcode);
        case 2u: return ExecuteTstEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteTstEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteTstEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteTstEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteTstEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteTstEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteTstEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecutePea(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteSwapDataRegister(opcode);
        case 2u: return ExecutePeaEffectiveAddress<&M68000::EffectiveAddressAddressIndirect>(opcode);
        case 5u: return ExecutePeaEffectiveAddress<&M68000::EffectiveAddressAddressDisplacement>(opcode);
        case 6u: return ExecutePeaEffectiveAddress<&M68000::EffectiveAddressAddressIndexControl>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecutePeaEffectiveAddress<&M68000::EffectiveAddressShort>(opcode);
                case 1u: return ExecutePeaEffectiveAddress<&M68000::EffectiveAddressLong>(opcode);
                case 2u: return ExecutePeaEffectiveAddress<&M68000::EffectiveAddressPCDisplacement>(opcode);
                case 3u: return ExecutePeaEffectiveAddress<&M68000::EffectiveAddressPCIndexControl>(opcode);
                [[unlikely]] default: return ExecuteIllegal();
            }
        [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteSingleOperationMisc(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: [[fallthrough]];
        case 1u: return ExecuteTrap(opcode);
        case 2u: return ExecuteLink(opcode);
        case 3u: return ExecuteUnlk(opcode);
        case 4u: return ExecuteMoveToUSP(opcode);
        case 5u: return ExecuteMoveFromUSP(opcode);
        case 6u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteReset();
                case 1u: return ExecuteNop();
                case 2u: return ExecuteStop();
                case 3u: return ExecuteRte();
                case 5u: return ExecuteRts();
                case 6u: return ExecuteTrapv();
                case 7u: return ExecuteRtr();
                    [[unlikely]]
                default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteMovemEffectiveAddress(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteExtDataRegister<T>(opcode);
        case 2u: return ExecuteMovemEffectiveAddress<&M68000::EffectiveAddressAddressIndirect, T>(opcode);
        case 4u: return ExecuteMovemEffectiveAddressAddressDecrement<T>(opcode);
        case 5u: return ExecuteMovemEffectiveAddress<&M68000::EffectiveAddressAddressDisplacement, T>(opcode);
        case 6u: return ExecuteMovemEffectiveAddress<&M68000::EffectiveAddressAddressIndex, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMovemEffectiveAddress<&M68000::EffectiveAddressShort, T>(opcode);
                case 1u: return ExecuteMovemEffectiveAddress<&M68000::EffectiveAddressLong, T>(opcode);
                    [[unlikely]]
                default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteMovemRegister(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 2u: return ExecuteMovemRegister<&M68000::EffectiveAddressAddressIndirect, T>(opcode);
        case 3u: return ExecuteMovemRegisterAddressIncrement<T>(opcode);
        case 5u: return ExecuteMovemRegister<&M68000::EffectiveAddressAddressDisplacement, T>(opcode);
        case 6u: return ExecuteMovemRegister<&M68000::EffectiveAddressAddressIndex, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMovemRegister<&M68000::EffectiveAddressShort, T>(opcode);
                case 1u: return ExecuteMovemRegister<&M68000::EffectiveAddressLong, T>(opcode);
                case 2u: return ExecuteMovemRegister<&M68000::EffectiveAddressPCDisplacement, T>(opcode);
                case 3u: return ExecuteMovemRegister<&M68000::EffectiveAddressPCIndex, T>(opcode);
                    [[unlikely]]
                default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteMoveFromSR(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteMoveFromSRDataRegister(opcode);
        case 2u: return ExecuteMoveFromSREffectiveAddress<&M68000::ReadFromAddressIndirect<Word>>(opcode);
        case 3u: return ExecuteMoveFromSREffectiveAddress<&M68000::ReadFromAddressIncrement<Word>>(opcode);
        case 4u: return ExecuteMoveFromSREffectiveAddress<&M68000::ReadFromAddressDecrement<Word>>(opcode);
        case 5u: return ExecuteMoveFromSREffectiveAddress<&M68000::ReadFromAddressDisplacement<Word>>(opcode);
        case 6u: return ExecuteMoveFromSREffectiveAddress<&M68000::ReadFromAddressIndex<Word>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveFromSREffectiveAddress<&M68000::ReadFromShort<Word>>(opcode);
                case 1u: return ExecuteMoveFromSREffectiveAddress<&M68000::ReadFromLong<Word>>(opcode);
                    [[unlikely]]
                default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteMoveToCCR(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteMoveToCCREffectiveAddress<&M68000::ReadFromDataRegister<Word>>(opcode);
        case 2u: return ExecuteMoveToCCREffectiveAddress<&M68000::ReadFromAddressIndirect<Word>>(opcode);
        case 3u: return ExecuteMoveToCCREffectiveAddress<&M68000::ReadFromAddressIncrement<Word>>(opcode);
        case 4u: return ExecuteMoveToCCREffectiveAddress<&M68000::ReadFromAddressDecrement<Word>>(opcode);
        case 5u: return ExecuteMoveToCCREffectiveAddress<&M68000::ReadFromAddressDisplacement<Word>>(opcode);
        case 6u: return ExecuteMoveToCCREffectiveAddress<&M68000::ReadFromAddressIndex<Word>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveToCCREffectiveAddress<&M68000::ReadFromShort<Word>>(opcode);
                case 1u: return ExecuteMoveToCCREffectiveAddress<&M68000::ReadFromLong<Word>>(opcode);
                case 2u: return ExecuteMoveToCCREffectiveAddress<&M68000::ReadFromPCDisplacement<Word>>(opcode);
                case 3u: return ExecuteMoveToCCREffectiveAddress<&M68000::ReadFromPCIndex<Word>>(opcode);
                case 4u: return ExecuteMoveToCCREffectiveAddress<&M68000::ReadFromImmediate<Word>>(opcode);
                    [[unlikely]]
                default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteMoveToSR(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteMoveToSREffectiveAddress<&M68000::ReadFromDataRegister<Word>>(opcode);
        case 2u: return ExecuteMoveToSREffectiveAddress<&M68000::ReadFromAddressIndirect<Word>>(opcode);
        case 3u: return ExecuteMoveToSREffectiveAddress<&M68000::ReadFromAddressIncrement<Word>>(opcode);
        case 4u: return ExecuteMoveToSREffectiveAddress<&M68000::ReadFromAddressDecrement<Word>>(opcode);
        case 5u: return ExecuteMoveToSREffectiveAddress<&M68000::ReadFromAddressDisplacement<Word>>(opcode);
        case 6u: return ExecuteMoveToSREffectiveAddress<&M68000::ReadFromAddressIndex<Word>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteMoveToSREffectiveAddress<&M68000::ReadFromShort<Word>>(opcode);
                case 1u: return ExecuteMoveToSREffectiveAddress<&M68000::ReadFromLong<Word>>(opcode);
                case 2u: return ExecuteMoveToSREffectiveAddress<&M68000::ReadFromPCDisplacement<Word>>(opcode);
                case 3u: return ExecuteMoveToSREffectiveAddress<&M68000::ReadFromPCIndex<Word>>(opcode);
                case 4u: return ExecuteMoveToSREffectiveAddress<&M68000::ReadFromImmediate<Word>>(opcode);
                    [[unlikely]]
                default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteTas(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteTasDataRegister(opcode);
        case 2u: return ExecuteTasEffectiveAddress<&M68000::ReadFromAddressIndirect<Byte>>(opcode);
        case 3u: return ExecuteTasEffectiveAddress<&M68000::ReadFromAddressIncrement<Byte>>(opcode);
        case 4u: return ExecuteTasEffectiveAddress<&M68000::ReadFromAddressDecrement<Byte>>(opcode);
        case 5u: return ExecuteTasEffectiveAddress<&M68000::ReadFromAddressDisplacement<Byte>>(opcode);
        case 6u: return ExecuteTasEffectiveAddress<&M68000::ReadFromAddressIndex<Byte>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteTasEffectiveAddress<&M68000::ReadFromShort<Byte>>(opcode);
                case 1u: return ExecuteTasEffectiveAddress<&M68000::ReadFromLong<Byte>>(opcode);
                case 4u: return ExecuteIllegal();
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteJsr(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 2u: return ExecuteJsrAddressIndirect(opcode);
        case 5u: return ExecuteJsr<&M68000::ControlAddressDisplacement>(opcode);
        case 6u: return ExecuteJsr<&M68000::ControlAddressIndex>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteJsr<&M68000::ControlShort>(opcode);
                case 1u: return ExecuteJsr<&M68000::ControlLong>(opcode);
                case 2u: return ExecuteJsr<&M68000::ControlPCDisplacement>(opcode);
                case 3u: return ExecuteJsr<&M68000::ControlPCIndex>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteJmp(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 2u: return ExecuteJmp<&M68000::ControlAddressIndirect>(opcode);
        case 5u: return ExecuteJmp<&M68000::ControlAddressDisplacement>(opcode);
        case 6u: return ExecuteJmp<&M68000::ControlAddressIndex>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteJmp < &M68000::ControlShort > (opcode);
                case 1u: return ExecuteJmp < &M68000::ControlLong > (opcode);
                case 2u: return ExecuteJmp < &M68000::ControlPCDisplacement > (opcode);
                case 3u: return ExecuteJmp < &M68000::ControlPCIndex > (opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteChk(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteChkDataRegister<&M68000::ReadFromDataRegister<Word>>(opcode);
        case 2u: return ExecuteChkDataRegister<&M68000::ReadFromAddressIndirect<Word>>(opcode);
        case 3u: return ExecuteChkDataRegister<&M68000::ReadFromAddressIncrement<Word>>(opcode);
        case 4u: return ExecuteChkDataRegister<&M68000::ReadFromAddressDecrement<Word>>(opcode);
        case 5u: return ExecuteChkDataRegister<&M68000::ReadFromAddressDisplacement<Word>>(opcode);
        case 6u: return ExecuteChkDataRegister<&M68000::ReadFromAddressIndex<Word>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteChkDataRegister<&M68000::ReadFromShort<Word>>(opcode);
                case 1u: return ExecuteChkDataRegister<&M68000::ReadFromLong<Word>>(opcode);
                case 2u: return ExecuteChkDataRegister<&M68000::ReadFromPCDisplacement<Word>>(opcode);
                case 3u: return ExecuteChkDataRegister<&M68000::ReadFromPCIndex<Word>>(opcode);
                case 4u: return ExecuteChkDataRegister<&M68000::ReadFromImmediate<Word>>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteLea(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 2u: return ExecuteLeaAddressRegister<&M68000::EffectiveAddressAddressIndirect>(opcode);
        case 5u: return ExecuteLeaAddressRegister<&M68000::EffectiveAddressAddressDisplacement>(opcode);
        case 6u: return ExecuteLeaAddressRegister<&M68000::EffectiveAddressAddressIndexControl>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteLeaAddressRegister<&M68000::EffectiveAddressShort>(opcode);
                case 1u: return ExecuteLeaAddressRegister<&M68000::EffectiveAddressLong>(opcode);
                case 2u: return ExecuteLeaAddressRegister<&M68000::EffectiveAddressPCDisplacement>(opcode);
                case 3u: return ExecuteLeaAddressRegister<&M68000::EffectiveAddressPCIndexControl>(opcode);
                [[unlikely]] default: return ExecuteIllegal();
            }
        [[unlikely]] default: return ExecuteIllegal();
    }
}

// NEGX.{B|W|L} Dy

template<typename T>
auto M68000::ExecuteNegxDataRegister(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadFromDataRegister<T>(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Negx<T>(y);
    WriteDataRegister<T>(ry, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
    }
}

// NEGX.{B|W|L} <ea>

template<auto Source, typename T>
auto M68000::ExecuteNegxEffectiveAddress(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Negx<T>(y);
    WriteMemory<T>(address, result);
}

// CLR.{B|W|L} Dy

template<typename T>
auto M68000::ExecuteClrDataRegister(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadFromDataRegister<T>(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Clr<T>(y);
    WriteDataRegister<T>(ry, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
    }
}

// CLR.{B|W|L} <ea>

template<auto Source, typename T>
auto M68000::ExecuteClrEffectiveAddress(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Clr<T>(y);
    WriteMemory<T>(address, result);
}

// NEG.{B|W|L} Dy

template<typename T>
auto M68000::ExecuteNegDataRegister(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadFromDataRegister<T>(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Neg<T>(y);
    WriteDataRegister<T>(ry, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
    }
}

// NEG.{B|W|L} <ea>

template<auto Source, typename T>
auto M68000::ExecuteNegEffectiveAddress(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Neg<T>(y);
    WriteMemory<T>(address, result);
}

// NOT.{B|W|L} Dy

template<typename T>
auto M68000::ExecuteNotDataRegister(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadFromDataRegister<T>(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Not<T>(y);
    WriteDataRegister<T>(ry, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
    }
}

// NOT.{B|W|L} <ea>

template<auto Source, typename T>
auto M68000::ExecuteNotEffectiveAddress(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Not<T>(y);
    WriteMemory<T>(address, result);
}

// NBCD.B Dy

template<typename T>
auto M68000::ExecuteNbcdDataRegister(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadFromDataRegister<T>(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Nbcd<T>(y);
    WriteDataRegister<T>(ry, result);
    InternalCycle();
}

// NBCD.B <ea>

template<auto Source, typename T>
auto M68000::ExecuteNbcdEffectiveAddress(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Nbcd<T>(y);
    WriteMemory<T>(address, result);
}

// TST.{B|W|L} Dy

template<typename T>
auto M68000::ExecuteTstDataRegister(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!ReadFromDataRegister<T>(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    Tst<T>(y);
}

// TST.{B|W|L} <ea>

template<auto Source, typename T>
auto M68000::ExecuteTstEffectiveAddress(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    Tst<T>(y);
}

// SWAP Dy

auto M68000::ExecuteSwapDataRegister(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Swap(y);
    WriteDataRegisterLong(ry, result);
    ExecuteFinalPrefetchCycle();
}

// PEA (An), PEA (d, An), PEA (d, PC)

template<auto Address>
auto M68000::ExecutePeaEffectiveAddress(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address;
    if (!(this->*Address)(ry, address)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    PushLong(address);
}

// TRAP #vector

auto M68000::ExecuteTrap(uint32_t opcode) -> void {
    RaiseTrapException(OpcodeTrapVector(opcode));
}

// LINK Ay, #imm

auto M68000::ExecuteLink(uint32_t opcode) -> void {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<Word>(rx, address, x)) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadAddressRegisterLong(ry);
    if (!PushLong(y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto sp = ReadSP();
    WriteAddressRegisterLong(ry, sp);
    WriteSP(sp + SignExtend16(x));
}

// UNLK Ay

auto M68000::ExecuteUnlk(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    const auto sp = ReadAddressRegisterLong(ry);
    WriteSP(sp);
    uint32_t y{};
    if (!PopLong(y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    WriteAddressRegisterLong(ry, y);
}

// MOVE Ay, USP

auto M68000::ExecuteMoveToUSP(uint32_t opcode) -> void {
    if (!ReadFlagS()) {
        RaisePrivilegeViolationException();
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadAddressRegisterLong(ry);
    WriteUSP(y);
}

// MOVE USP, Ay

auto M68000::ExecuteMoveFromUSP(uint32_t opcode) -> void {
    if (!ReadFlagS()) {
        RaisePrivilegeViolationException();
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    WriteAddressRegisterLong(ry, ReadUSP());
}

// RESET

auto M68000::ExecuteReset() -> void {
    if (!ReadFlagS()) {
        RaisePrivilegeViolationException();
        return;
    }
    InternalCycle();
    InternalCycle();
    ResetExternalDevices();
    ElapseCycles(124u);
    ExecuteFinalPrefetchCycle();
}

// NOP

auto M68000::ExecuteNop() -> void {
    ExecuteFinalPrefetchCycle();
}

// STOP

auto M68000::ExecuteStop() -> void {
    if (!ReadFlagS()) {
        RaisePrivilegeViolationException();
        return;
    }
    InternalCycle();
    InternalCycle();
    WriteSR(ReadIRC());
    WritePC(ReadPC() + 4u);
    WriteStopped(true);
}

// RTE

auto M68000::ExecuteRte() -> void {
    if (!ReadFlagS()) {
        RaisePrivilegeViolationException();
        return;
    }
    uint32_t sr, target;
    const auto success = PopWord(sr) &&
                         PopLong(target);
    if (!success) [[unlikely]] {
        return;
    }
    WriteSR(sr);
    Jump(target);
}

// RTS

auto M68000::ExecuteRts() -> void {
    uint32_t target;
    if (!PopLong(target)) [[unlikely]] {
        return;
    }
    Jump(target);
}

// TRAPV

auto M68000::ExecuteTrapv() -> void {
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    if (!ReadFlagV()) {
        return;
    }
    RaiseTrapvException();
}

// RTR

auto M68000::ExecuteRtr() -> void {
    uint32_t ccr, target;
    const auto success = PopWord(ccr) &&
                         PopLong(target);
    if (!success) [[unlikely]] {
        return;
    }
    WriteCCR(ccr);
    Jump(target);
}

// EXT.{W|L} Dy

template<typename T>
auto M68000::ExecuteExtDataRegister(uint32_t opcode) -> void {
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Ext<T>(y);
    WriteDataRegister<T>(ry, result);
}

// MOVEM.{W|L} <list>, <ea>

template<auto Address, typename T>
auto M68000::ExecuteMovemEffectiveAddress(uint32_t opcode) -> void {
    uint32_t rx{}, address{}, list;
    if (!ReadFromImmediate<Word>(rx, address, list)) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    if (!(this->*Address)(ry, address)) [[unlikely]] {
        return;
    }
    if (!ExecuteRegisterListEffectiveAddress<T>(list, address)) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}

template<typename T>
auto M68000::ExecuteRegisterListEffectiveAddress(uint32_t list, uint32_t address) -> bool {
    for (auto i = 0u; i < 16u; ++i) {
        if (list & (1u << i)) {
            const auto value = (i < 8u) ?
                               ReadDataRegisterLong(i) :
                               ReadAddressRegisterLong(i - 8u);
            if (!WriteMemory<T>(address, value)) [[unlikely]] {
                return false;
            }
            address += T::ADDRESS_INCREMENT;
        }
    }
    return true;
}

// MOVEM.{W|L} <list>, -(Ay)

template<typename T>
auto M68000::ExecuteMovemEffectiveAddressAddressDecrement(uint32_t opcode) -> void {
    uint32_t rx{}, address{}, list;
    if (!ReadFromImmediate<Word>(rx, address, list)) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    if (!EffectiveAddressAddressIndirect(ry, address)) [[unlikely]] {
        return;
    }
    if (!ExecuteRegisterListAddressDecrement<T>(list, address)) [[unlikely]] {
        return;
    }
    WriteAddressRegisterLong(ry, address);
    ExecuteFinalPrefetchCycle();
}

template<typename T>
auto M68000::ExecuteRegisterListAddressDecrement(uint32_t list, uint32_t& address) -> bool {
    for (auto i = 0u; i < 16u; ++i) {
        if (list & (1u << i)) {
            address -= T::ADDRESS_INCREMENT;
            const auto value = (i < 8u) ?
                               ReadAddressRegisterLong(7u - i) :
                               ReadDataRegisterLong(15u - i);
            if (!WriteMemory<T>(address, value)) [[unlikely]] {
                return false;
            }
        }
    }
    return true;
}

// MOVEM.{W|L} <ea>, <list>

template<auto Address, typename T>
auto M68000::ExecuteMovemRegister(uint32_t opcode) -> void {
    uint32_t rx{}, address{}, list;
    if (!ReadFromImmediate<Word>(rx, address, list)) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    if (!(this->*Address)(ry, address)) [[unlikely]] {
        return;
    }
    if (!ExecuteRegisterListRegister<T>(list, address)) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}

// MOVEM.{W|L} (Ay)+, <list>

template<typename T>
auto M68000::ExecuteMovemRegisterAddressIncrement(uint32_t opcode) -> void {
    uint32_t rx{}, address{}, list;
    if (!ReadFromImmediate<Word>(rx, address, list)) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    if (!EffectiveAddressAddressIndirect(ry, address)) [[unlikely]] {
        return;
    }
    if (!ExecuteRegisterListRegister<T>(list, address)) [[unlikely]] {
        return;
    }
    WriteAddressRegisterLong(ry, address);
    ExecuteFinalPrefetchCycle();
}

template<typename T>
auto M68000::ExecuteRegisterListRegister(uint32_t list, uint32_t& address) -> bool {
    uint32_t value;
    for (auto i = 0u; i < 16u; ++i) {
        if (list & (1u << i)) {
            if (!ReadMemory<T>(address, value)) [[unlikely]] {
                return false;
            }
            const auto extended = T::SignExtend(value);
            if (i < 8u) {
                WriteDataRegisterLong(i, extended);
            } else {
                WriteAddressRegisterLong(i - 8u, extended);
            }
            address += T::ADDRESS_INCREMENT;
        }
    }
    return ReadMemory<Word>(address, value);
}

// MOVE.W SR, Dy

auto M68000::ExecuteMoveFromSRDataRegister(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    const auto result = ReadSR();
    WriteDataRegister<Word>(ry, result);
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    InternalCycle();
}

// MOVE.W SR, <ea>

template<auto Source>
auto M68000::ExecuteMoveFromSREffectiveAddress(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = ReadSR();
    WriteMemory<Word>(address, result);
}

// MOVE.W <ea>, CCR

template<auto Source>
auto M68000::ExecuteMoveToCCREffectiveAddress(uint32_t opcode) -> void {
    // Note: the bus access patterns need verifying
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    InternalCycle();
    InternalCycle();
    WriteCCR(y);
    WritePC(ReadPC() - 2u);
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
}

// MOVE.W <ea>, SR

template<auto Source>
auto M68000::ExecuteMoveToSREffectiveAddress(uint32_t opcode) -> void {
    if (!ReadFlagS()) {
        RaisePrivilegeViolationException();
        return;
    }
    // Note: the bus access patterns need verifying
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    InternalCycle();
    InternalCycle();
    WriteSR(y);
    WritePC(ReadPC() - 2u);
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
}

// TAS Dy

auto M68000::ExecuteTasDataRegister(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Tas(y);
    WriteDataRegister<Byte>(ry, result);
    ExecuteFinalPrefetchCycle();
}

// TAS <ea>

template<auto Source>
auto M68000::ExecuteTasEffectiveAddress(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    InternalCycle();
    const auto result = Tas(y);
    if (!WriteMemory<Byte>(address, result)) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}


// JSR (An)

auto M68000::ExecuteJsrAddressIndirect(uint32_t opcode) -> void {
    uint32_t target;
    if (!ControlAddressIndirect(OpcodeRegisterY(opcode), target)) [[unlikely]] {
        return;
    }
    JumpSubroutine(ReadPC() + 2u, target);
}

// JSR <ea>

template<auto Control>
auto M68000::ExecuteJsr(uint32_t opcode) -> void {
    uint32_t target;
    if (!(this->*Control)(OpcodeRegisterY(opcode), target)) [[unlikely]] {
        return;
    }
    JumpSubroutine(ReadPC() + 4u, target);
}

// JMP <ea>

template<auto Control>
auto M68000::ExecuteJmp(uint32_t opcode) -> void {
    uint32_t target;
    if (!(this->*Control)(OpcodeRegisterY(opcode), target)) [[unlikely]] {
        return;
    }
    Jump(target);
}

// CHK <ea>, Dx

template<auto Source>
auto M68000::ExecuteChkDataRegister(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto rx = OpcodeRegisterX(opcode);
    const auto x = Truncate16(ReadDataRegisterLong(rx));
    if ((x & 0x8000u) || (y & 0x8000u) || (x > y)) {
        WriteFlagN<Word>(x);
        RaiseChkException();
        return;
    }
    InternalCycle();
    InternalCycle();
    InternalCycle();
}

// LEA <ea>, Ax

template<auto Address>
auto M68000::ExecuteLeaAddressRegister(uint32_t opcode) -> void {
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t effectiveAddress;
    if (!(this->*Address)(ry, effectiveAddress)) [[unlikely]] {
        return;
    }
    const auto rx = OpcodeRegisterX(opcode);
    WriteAddressRegisterLong(rx, effectiveAddress);
    ExecuteFinalPrefetchCycle();
}