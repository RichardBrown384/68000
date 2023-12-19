#include "M68000/M68000.h"
#include "M68000/M68000_Opcode.h"
#include "M68000/M68000_Int.h"
#include "M68000/M68000_EffectiveAddress.h"
#include "M68000/M68000_Operations.h"

using namespace rbrown::m68000;

auto M68000::ExecuteLine0(uint32_t opcode) -> void {
    switch (OpcodeModeX(opcode)) {
        case 0u: return ExecuteImmediateOperationByte(opcode);
        case 1u: return ExecuteImmediateOperationWord(opcode);
        case 2u: return ExecuteImmediateOperationLong(opcode);
        case 3u: return ExecuteImmediateOperationBset(opcode);
        case 4u: return ExecuteBtstDynamic(opcode);
        case 5u: return ExecuteBchgDynamic(opcode);
        case 6u: return ExecuteBclrDynamic(opcode);
        case 7u: return ExecuteBsetDynamic(opcode);
        [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteImmediateOperationByte(uint32_t opcode) -> void {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return ExecuteOrImmediate<Byte>(opcode);
        case 1u: return ExecuteAndImmediate<Byte>(opcode);
        case 2u: return ExecuteSubImmediate<Byte>(opcode);
        case 3u: return ExecuteAddImmediate<Byte>(opcode);
        case 4u: return ExecuteBtstStatic(opcode);
        case 5u: return ExecuteEorImmediate<Byte>(opcode);
        case 6u: return ExecuteCmpImmediate<Byte>(opcode);
        [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteImmediateOperationWord(uint32_t opcode) -> void {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return ExecuteOrImmediate<Word>(opcode);
        case 1u: return ExecuteAndImmediate<Word>(opcode);
        case 2u: return ExecuteSubImmediate<Word>(opcode);
        case 3u: return ExecuteAddImmediate<Word>(opcode);
        case 4u: return ExecuteBchgStatic(opcode);
        case 5u: return ExecuteEorImmediate<Word>(opcode);
        case 6u: return ExecuteCmpImmediate<Word>(opcode);
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteImmediateOperationLong(uint32_t opcode) -> void {
    switch (OpcodeRegisterX(opcode)) {
        case 0u: return ExecuteOrImmediate<Long>(opcode);
        case 1u: return ExecuteAndImmediate<Long>(opcode);
        case 2u: return ExecuteSubImmediate<Long>(opcode);
        case 3u: return ExecuteAddImmediate<Long>(opcode);
        case 4u: return ExecuteBclrStatic(opcode);
        case 5u: return ExecuteEorImmediate<Long>(opcode);
        case 6u: return ExecuteCmpImmediate<Long>(opcode);
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteImmediateOperationBset(uint32_t opcode) -> void {
    switch (OpcodeRegisterX(opcode)) {
        case 4u: return ExecuteBsetStatic(opcode);
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteBtstDynamic(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteBtstDynamicDataRegister(opcode);
        case 1u: return ExecuteMovepWordDataRegister(opcode);
        case 2u: return ExecuteBtstDynamicEffectiveAddress<&M68000::ReadFromAddressIndirect<Byte>>(opcode);
        case 3u: return ExecuteBtstDynamicEffectiveAddress<&M68000::ReadFromAddressIncrement<Byte>>(opcode);
        case 4u: return ExecuteBtstDynamicEffectiveAddress<&M68000::ReadFromAddressDecrement<Byte>>(opcode);
        case 5u: return ExecuteBtstDynamicEffectiveAddress<&M68000::ReadFromAddressDisplacement<Byte>>(opcode);
        case 6u: return ExecuteBtstDynamicEffectiveAddress<&M68000::ReadFromAddressIndex<Byte>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBtstDynamicEffectiveAddress<&M68000::ReadFromShort<Byte>>(opcode);
                case 1u: return ExecuteBtstDynamicEffectiveAddress<&M68000::ReadFromLong<Byte>>(opcode);
                case 2u: return ExecuteBtstDynamicEffectiveAddress<&M68000::ReadFromPCDisplacement<Byte>>(opcode);
                case 3u: return ExecuteBtstDynamicEffectiveAddress<&M68000::ReadFromPCIndex<Byte>>(opcode);
                case 4u: return ExecuteBtstDynamicEffectiveAddress<&M68000::ReadFromImmediate<Byte>>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteBchgDynamic(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteBchgDynamicDataRegister(opcode);
        case 1u: return ExecuteMovepLongDataRegister(opcode);
        case 2u: return ExecuteBchgDynamicEffectiveAddress<&M68000::ReadFromAddressIndirect<Byte>>(opcode);
        case 3u: return ExecuteBchgDynamicEffectiveAddress<&M68000::ReadFromAddressIncrement<Byte>>(opcode);
        case 4u: return ExecuteBchgDynamicEffectiveAddress<&M68000::ReadFromAddressDecrement<Byte>>(opcode);
        case 5u: return ExecuteBchgDynamicEffectiveAddress<&M68000::ReadFromAddressDisplacement<Byte>>(opcode);
        case 6u: return ExecuteBchgDynamicEffectiveAddress<&M68000::ReadFromAddressIndex<Byte>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBchgDynamicEffectiveAddress<&M68000::ReadFromShort<Byte>>(opcode);
                case 1u: return ExecuteBchgDynamicEffectiveAddress<&M68000::ReadFromLong<Byte>>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteBclrDynamic(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteBclrDynamicDataRegister(opcode);
        case 1u: return ExecuteMovepWordAddressDisplacement(opcode);
        case 2u: return ExecuteBclrDynamicEffectiveAddress<&M68000::ReadFromAddressIndirect<Byte>>(opcode);
        case 3u: return ExecuteBclrDynamicEffectiveAddress<&M68000::ReadFromAddressIncrement<Byte>>(opcode);
        case 4u: return ExecuteBclrDynamicEffectiveAddress<&M68000::ReadFromAddressDecrement<Byte>>(opcode);
        case 5u: return ExecuteBclrDynamicEffectiveAddress<&M68000::ReadFromAddressDisplacement<Byte>>(opcode);
        case 6u: return ExecuteBclrDynamicEffectiveAddress<&M68000::ReadFromAddressIndex<Byte>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBclrDynamicEffectiveAddress<&M68000::ReadFromShort<Byte>>(opcode);
                case 1u: return ExecuteBclrDynamicEffectiveAddress<&M68000::ReadFromLong<Byte>>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteBsetDynamic(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteBsetDynamicDataRegister(opcode);
        case 1u: return ExecuteMovepLongAddressDisplacement(opcode);
        case 2u: return ExecuteBsetDynamicEffectiveAddress<&M68000::ReadFromAddressIndirect<Byte>>(opcode);
        case 3u: return ExecuteBsetDynamicEffectiveAddress<&M68000::ReadFromAddressIncrement<Byte>>(opcode);
        case 4u: return ExecuteBsetDynamicEffectiveAddress<&M68000::ReadFromAddressDecrement<Byte>>(opcode);
        case 5u: return ExecuteBsetDynamicEffectiveAddress<&M68000::ReadFromAddressDisplacement<Byte>>(opcode);
        case 6u: return ExecuteBsetDynamicEffectiveAddress<&M68000::ReadFromAddressIndex<Byte>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBsetDynamicEffectiveAddress<&M68000::ReadFromShort<Byte>>(opcode);
                case 1u: return ExecuteBsetDynamicEffectiveAddress<&M68000::ReadFromLong<Byte>>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteOrImmediate(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteOrImmediateDataRegister<T>(opcode);
        case 2u: return ExecuteOrImmediateEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteOrImmediateEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteOrImmediateEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteOrImmediateEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteOrImmediateEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteOrImmediateEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteOrImmediateEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                case 4u:
                    if (std::is_same_v<T, Byte>) {
                        return ExecuteOrImmediateCCR();
                    } else if (std::is_same_v<T, Word>) {
                        return ExecuteOrImmediateSR();
                    } else {
                        return ExecuteIllegal();
                    }
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteAndImmediate(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteAndImmediateDataRegister<T>(opcode);
        case 2u: return ExecuteAndImmediateEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteAndImmediateEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteAndImmediateEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteAndImmediateEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteAndImmediateEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteAndImmediateEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteAndImmediateEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                case 4u:
                    if (std::is_same_v<T, Byte>) {
                        return ExecuteAndImmediateCCR();
                    } else if (std::is_same_v<T, Word>) {
                        return ExecuteAndImmediateSR();
                    } else {
                        return ExecuteIllegal();
                    }
                [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteSubImmediate(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteSubImmediateDataRegister<T>(opcode);
        case 2u: return ExecuteSubImmediateEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteSubImmediateEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteSubImmediateEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteSubImmediateEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteSubImmediateEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteSubImmediateEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteSubImmediateEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteAddImmediate(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteAddImmediateDataRegister<T>(opcode);
        case 2u: return ExecuteAddImmediateEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteAddImmediateEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteAddImmediateEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteAddImmediateEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteAddImmediateEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteAddImmediateEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteAddImmediateEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteBtstStatic(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteBtstStaticDataRegister(opcode);
        case 2u: return ExecuteBtstStaticEffectiveAddress<&M68000::ReadFromAddressIndirect<Byte>>(opcode);
        case 3u: return ExecuteBtstStaticEffectiveAddress<&M68000::ReadFromAddressIncrement<Byte>>(opcode);
        case 4u: return ExecuteBtstStaticEffectiveAddress<&M68000::ReadFromAddressDecrement<Byte>>(opcode);
        case 5u: return ExecuteBtstStaticEffectiveAddress<&M68000::ReadFromAddressDisplacement<Byte>>(opcode);
        case 6u: return ExecuteBtstStaticEffectiveAddress<&M68000::ReadFromAddressIndex<Byte>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBtstStaticEffectiveAddress<&M68000::ReadFromShort<Byte>>(opcode);
                case 1u: return ExecuteBtstStaticEffectiveAddress<&M68000::ReadFromLong<Byte>>(opcode);
                case 2u: return ExecuteBtstStaticEffectiveAddress<&M68000::ReadFromPCDisplacement<Byte>>(opcode);
                case 3u: return ExecuteBtstStaticEffectiveAddress<&M68000::ReadFromPCIndex<Byte>>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteEorImmediate(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteEorImmediateDataRegister<T>(opcode);
        case 2u: return ExecuteEorImmediateEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteEorImmediateEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteEorImmediateEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteEorImmediateEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteEorImmediateEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteEorImmediateEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteEorImmediateEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                case 4u:
                    if (std::is_same_v<T, Byte>) {
                        return ExecuteEorImmediateCCR();
                    } else if (std::is_same_v<T, Word>) {
                        return ExecuteEorImmediateSR();
                    } else {
                        return ExecuteIllegal();
                    }
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

template<typename T>
auto M68000::ExecuteCmpImmediate(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteCmpImmediateDataRegister<T>(opcode);
        case 2u: return ExecuteCmpImmediateEffectiveAddress<&M68000::ReadFromAddressIndirect<T>, T>(opcode);
        case 3u: return ExecuteCmpImmediateEffectiveAddress<&M68000::ReadFromAddressIncrement<T>, T>(opcode);
        case 4u: return ExecuteCmpImmediateEffectiveAddress<&M68000::ReadFromAddressDecrement<T>, T>(opcode);
        case 5u: return ExecuteCmpImmediateEffectiveAddress<&M68000::ReadFromAddressDisplacement<T>, T>(opcode);
        case 6u: return ExecuteCmpImmediateEffectiveAddress<&M68000::ReadFromAddressIndex<T>, T>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteCmpImmediateEffectiveAddress<&M68000::ReadFromShort<T>, T>(opcode);
                case 1u: return ExecuteCmpImmediateEffectiveAddress<&M68000::ReadFromLong<T>, T>(opcode);
                [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteBchgStatic(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteBchgStaticDataRegister(opcode);
        case 2u: return ExecuteBchgStaticEffectiveAddress<&M68000::ReadFromAddressIndirect<Byte>>(opcode);
        case 3u: return ExecuteBchgStaticEffectiveAddress<&M68000::ReadFromAddressIncrement<Byte>>(opcode);
        case 4u: return ExecuteBchgStaticEffectiveAddress<&M68000::ReadFromAddressDecrement<Byte>>(opcode);
        case 5u: return ExecuteBchgStaticEffectiveAddress<&M68000::ReadFromAddressDisplacement<Byte>>(opcode);
        case 6u: return ExecuteBchgStaticEffectiveAddress<&M68000::ReadFromAddressIndex<Byte>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBchgStaticEffectiveAddress<&M68000::ReadFromShort<Byte>>(opcode);
                case 1u: return ExecuteBchgStaticEffectiveAddress<&M68000::ReadFromLong<Byte>>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteBclrStatic(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteBclrStaticDataRegister(opcode);
        case 2u: return ExecuteBclrStaticEffectiveAddress<&M68000::ReadFromAddressIndirect<Byte>>(opcode);
        case 3u: return ExecuteBclrStaticEffectiveAddress<&M68000::ReadFromAddressIncrement<Byte>>(opcode);
        case 4u: return ExecuteBclrStaticEffectiveAddress<&M68000::ReadFromAddressDecrement<Byte>>(opcode);
        case 5u: return ExecuteBclrStaticEffectiveAddress<&M68000::ReadFromAddressDisplacement<Byte>>(opcode);
        case 6u: return ExecuteBclrStaticEffectiveAddress<&M68000::ReadFromAddressIndex<Byte>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBclrStaticEffectiveAddress<&M68000::ReadFromShort<Byte>>(opcode);
                case 1u: return ExecuteBclrStaticEffectiveAddress<&M68000::ReadFromLong<Byte>>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

auto M68000::ExecuteBsetStatic(uint32_t opcode) -> void {
    switch (OpcodeModeY(opcode)) {
        case 0u: return ExecuteBsetStaticDataRegister(opcode);
        case 2u: return ExecuteBsetStaticEffectiveAddress<&M68000::ReadFromAddressIndirect<Byte>>(opcode);
        case 3u: return ExecuteBsetStaticEffectiveAddress<&M68000::ReadFromAddressIncrement<Byte>>(opcode);
        case 4u: return ExecuteBsetStaticEffectiveAddress<&M68000::ReadFromAddressDecrement<Byte>>(opcode);
        case 5u: return ExecuteBsetStaticEffectiveAddress<&M68000::ReadFromAddressDisplacement<Byte>>(opcode);
        case 6u: return ExecuteBsetStaticEffectiveAddress<&M68000::ReadFromAddressIndex<Byte>>(opcode);
        case 7u:
            switch (OpcodeRegisterY(opcode)) {
                case 0u: return ExecuteBsetStaticEffectiveAddress<&M68000::ReadFromShort<Byte>>(opcode);
                case 1u: return ExecuteBsetStaticEffectiveAddress<&M68000::ReadFromLong<Byte>>(opcode);
                    [[unlikely]] default: return ExecuteIllegal();
            }
            [[unlikely]] default: return ExecuteIllegal();
    }
}

// ORI.{B|W|L} #imm, Dy

template<typename T>
auto M68000::ExecuteOrImmediateDataRegister(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<T>(rx, address, x)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Or<T>(x, y);
    WriteDataRegister<T>(ry, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
        InternalCycle();
    }
}

// ORI.{B|W|L} #imm, <ea>

template<auto Source, typename T>
auto M68000::ExecuteOrImmediateEffectiveAddress(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<T>(rx, address, x)) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Or<T>(x, y);
    WriteMemory<T>(address, result);
}

// ORI.B #imm, CCR

auto M68000::ExecuteOrImmediateCCR() -> void {
    // TODO: work out the bus addresses for prefetch
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<Byte>(rx, address, x)) [[unlikely]] {
        return;
    }
    InternalCycle();
    InternalCycle();
    InternalCycle();
    InternalCycle();
    WritePC(ReadPC() - 2u);
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto y = ReadCCR();
    WriteCCR(x | y);
}

// ORI.W #imm, SR

auto M68000::ExecuteOrImmediateSR() -> void {
    // TODO: work out the bus addresses for prefetch
    if (!ReadFlagS()) {
        RaisePrivilegeViolationException();
        return;
    }
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<Word>(rx, address, x)) [[unlikely]] {
        return;
    }
    InternalCycle();
    InternalCycle();
    InternalCycle();
    InternalCycle();
    WritePC(ReadPC() - 2u);
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto y = ReadSR();
    WriteSR(x | y);
}

// ANDI.{B|W|L} #imm, Dy

template<typename T>
auto M68000::ExecuteAndImmediateDataRegister(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<T>(rx, address, x)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = And<T>(x, y);
    WriteDataRegister<T>(ry, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
        InternalCycle();
    }
}

// ANDI.{B|W|L} #imm, <ea>

template<auto Source, typename T>
auto M68000::ExecuteAndImmediateEffectiveAddress(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<T>(rx, address, x)) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = And<T>(x, y);
    WriteMemory<T>(address, result);
}

// ANDI.B #imm, CCR

auto M68000::ExecuteAndImmediateCCR() -> void {
    // TODO: work out the bus addresses for prefetch
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<Byte>(rx, address, x)) [[unlikely]] {
        return;
    }
    InternalCycle();
    InternalCycle();
    InternalCycle();
    InternalCycle();
    WritePC(ReadPC() - 2u);
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto y = ReadCCR();
    WriteCCR(x & y);
}

// ANDI.W #imm, SR

auto M68000::ExecuteAndImmediateSR() -> void {
    // TODO: work out the bus addresses for prefetch
    if (!ReadFlagS()) {
        RaisePrivilegeViolationException();
        return;
    }
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<Word>(rx, address, x)) [[unlikely]] {
        return;
    }
    InternalCycle();
    InternalCycle();
    InternalCycle();
    InternalCycle();
    WritePC(ReadPC() - 2u);
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto y = ReadSR();
    WriteSR(x & y);
}

// SUBI.{B|W|L} #imm, Dy

template<typename T>
auto M68000::ExecuteSubImmediateDataRegister(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<T>(rx, address, x)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Sub<T>(x, y);
    WriteDataRegister<T>(ry, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
        InternalCycle();
    }
}

// SUBI.{B|W|L} #imm, <ea>

template<auto Source, typename T>
auto M68000::ExecuteSubImmediateEffectiveAddress(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<T>(rx, address, x)) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Sub<T>(x, y);
    WriteMemory<T>(address, result);
}

// ADDI.{B|W|L} #imm, Dy

template<typename T>
auto M68000::ExecuteAddImmediateDataRegister(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<T>(rx, address, x)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Add<T>(x, y);
    WriteDataRegister<T>(ry, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
        InternalCycle();
    }
}

// ADDI.{B|W|L} #imm, <ea>

template<auto Source, typename T>
auto M68000::ExecuteAddImmediateEffectiveAddress(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<T>(rx, address, x)) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Add<T>(x, y);
    WriteMemory<T>(address, result);
}

// EORI.{B|W|L} #imm, Dy

template<typename T>
auto M68000::ExecuteEorImmediateDataRegister(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<T>(rx, address, x)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Eor<T>(x, y);
    WriteDataRegister<T>(ry, result);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
        InternalCycle();
    }
}

// EORI.{B|W|L} #imm, <ea>

template<auto Source, typename T>
auto M68000::ExecuteEorImmediateEffectiveAddress(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<T>(rx, address, x)) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Eor<T>(x, y);
    WriteMemory<T>(address, result);
}

// EORI.B #imm, CCR

auto M68000::ExecuteEorImmediateCCR() -> void {
    // TODO: work out the bus addresses for prefetch
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<Byte>(rx, address, x)) [[unlikely]] {
        return;
    }
    InternalCycle();
    InternalCycle();
    InternalCycle();
    InternalCycle();
    WritePC(ReadPC() - 2u);
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto y = ReadCCR();
    WriteCCR(x ^ y);
}

// EORI.W #imm, SR

auto M68000::ExecuteEorImmediateSR() -> void {
    // TODO: work out the bus addresses for prefetch
    if (!ReadFlagS()) {
        RaisePrivilegeViolationException();
        return;
    }
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<Word>(rx, address, x)) [[unlikely]] {
        return;
    }
    InternalCycle();
    InternalCycle();
    InternalCycle();
    InternalCycle();
    WritePC(ReadPC() - 2u);
    if (!ExecutePrefetchCycle()) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto y = ReadSR();
    WriteSR(x ^ y);
}

// CMPI.{B|W|L} #imm, Dy

template<typename T>
auto M68000::ExecuteCmpImmediateDataRegister(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<T>(rx, address, x)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    Cmp<T>(x, y);
    if constexpr(std::is_same_v<T, Long>) {
        InternalCycle();
    }
}

// CMPI.{B|W|L} #imm, <ea>

template<auto Source, typename T>
auto M68000::ExecuteCmpImmediateEffectiveAddress(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<T>(rx, address, x)) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    Cmp<T>(x, y);
}

// BTST.L #imm, Dy

auto M68000::ExecuteBtstStaticDataRegister(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<Byte>(rx, address, x)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    Btst<Long>(x, y);
    InternalCycle();
}

// BTST.B #imm, <ea>

template<auto Source>
auto M68000::ExecuteBtstStaticEffectiveAddress(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<Byte>(rx, address, x)) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    Btst<Byte>(x, y);
}

// BCHG.L #imm, Dy

auto M68000::ExecuteBchgStaticDataRegister(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<Byte>(rx, address, x)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Bchg<Long>(x, y);
    WriteDataRegister<Long>(ry, result);
    InternalCycle();
    InternalCycle();
}

// BCHG.B #imm, <ea>

template<auto Source>
auto M68000::ExecuteBchgStaticEffectiveAddress(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<Byte>(rx, address, x)) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Bchg<Byte>(x, y);
    WriteMemory<Byte>(address, result);
}

// BCLR.L #imm, Dy

auto M68000::ExecuteBclrStaticDataRegister(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<Byte>(rx, address, x)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Bclr<Long>(x, y);
    WriteDataRegister<Long>(ry, result);
    InternalCycle();
    InternalCycle();
    InternalCycle();
}

// BCLR.B #imm, <ea>

template<auto Source>
auto M68000::ExecuteBclrStaticEffectiveAddress(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<Byte>(rx, address, x)) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Bclr<Byte>(x, y);
    WriteMemory<Byte>(address, result);
}

// BSET.L #imm, Dy

auto M68000::ExecuteBsetStaticDataRegister(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<Byte>(rx, address, x)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    const auto y = ReadDataRegisterLong(ry);
    const auto result = Bset<Long>(x, y);
    WriteDataRegister<Long>(ry, result);
    InternalCycle();
    InternalCycle();
}

// BSET.B #imm, <ea>

template<auto Source>
auto M68000::ExecuteBsetStaticEffectiveAddress(uint32_t opcode) -> void  {
    uint32_t rx{}, address{}, x;
    if (!ReadFromImmediate<Byte>(rx, address, x)) [[unlikely]] {
        return;
    }
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Bset<Byte>(x, y);
    WriteMemory<Byte>(address, result);
}

// BTST.L Dx, Dy

auto M68000::ExecuteBtstDynamicDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    const auto y = ReadDataRegisterLong(ry);
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    Btst<Long>(x, y);
    InternalCycle();
}

// BTST.B Dx, <ea>

template<auto Source>
auto M68000::ExecuteBtstDynamicEffectiveAddress(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    Btst<Byte>(x, y);
}

// BCHG.L Dx, Dy

auto M68000::ExecuteBchgDynamicDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    const auto y = ReadDataRegisterLong(ry);
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Bchg<Long>(x, y);
    WriteDataRegister<Long>(ry, result);
    InternalCycle();
    InternalCycle();
}

// BCHG.B Dx, <ea>

template<auto Source>
auto M68000::ExecuteBchgDynamicEffectiveAddress(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Bchg<Byte>(x, y);
    WriteMemory<Byte>(address, result);
}

// BCLR.L Dx, Dy

auto M68000::ExecuteBclrDynamicDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    const auto y = ReadDataRegisterLong(ry);
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Bclr<Long>(x, y);
    WriteDataRegister<Long>(ry, result);
    InternalCycle();
    InternalCycle();
    InternalCycle();
}

// BCLR.B Dx, <ea>

template<auto Source>
auto M68000::ExecuteBclrDynamicEffectiveAddress(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Bclr<Byte>(x, y);
    WriteMemory<Byte>(address, result);
}

// BSET.L Dx, Dy

auto M68000::ExecuteBsetDynamicDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    const auto y = ReadDataRegisterLong(ry);
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Bset<Long>(x, y);
    WriteDataRegister<Long>(ry, result);
    InternalCycle();
    InternalCycle();
}

// BSET.B Dx, <ea>

template<auto Source>
auto M68000::ExecuteBsetDynamicEffectiveAddress(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    uint32_t address, y;
    if (!(this->*Source)(ry, address, y)) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    const auto result = Bset<Byte>(x, y);
    WriteMemory<Byte>(address, result);
}

// MOVEP.W (d, Ay), Dx

auto M68000::ExecuteMovepWordDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t effectiveAddress{};
    if (!EffectiveAddressAddressDisplacement(ry, effectiveAddress)) [[unlikely]] {
        return;
    }
    uint32_t b1, b0;
    const bool success = ReadByte(effectiveAddress, b1) &&
                         ReadByte(effectiveAddress + 2u, b0);
    if (!success) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    WriteDataRegister<Word>(rx, Pack16(b0, b1));
}

// MOVEP.L (d, Ay), Dx

auto M68000::ExecuteMovepLongDataRegister(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    uint32_t effectiveAddress{};
    if (!EffectiveAddressAddressDisplacement(ry, effectiveAddress)) [[unlikely]] {
        return;
    }
    uint32_t b3, b2, b1, b0;
    const auto success = ReadByte(effectiveAddress, b3) &&
                         ReadByte(effectiveAddress + 2u, b2) &&
                         ReadByte(effectiveAddress + 4u, b1) &&
                         ReadByte(effectiveAddress + 6u, b0);
    if (!success) [[unlikely]] {
        return;
    }
    if (!ExecuteFinalPrefetchCycle()) [[unlikely]] {
        return;
    }
    WriteDataRegister<Long>(rx, Pack32(b0, b1, b2, b3));
}

// MOVEP.W Dx, (d, Ay)

auto M68000::ExecuteMovepWordAddressDisplacement(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    uint32_t effectiveAddress{};
    if (!EffectiveAddressAddressDisplacement(ry, effectiveAddress)) [[unlikely]] {
        return;
    }
    const auto success = WriteByte(effectiveAddress, x >> 8u) &&
                         WriteByte(effectiveAddress + 2u, x);
    if (!success) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}

// MOVEP.L Dx, (d, Ay)

auto M68000::ExecuteMovepLongAddressDisplacement(uint32_t opcode) -> void {
    const auto rx = OpcodeRegisterX(opcode);
    const auto ry = OpcodeRegisterY(opcode);
    const auto x = ReadDataRegisterLong(rx);
    uint32_t effectiveAddress{};
    if (!EffectiveAddressAddressDisplacement(ry, effectiveAddress)) [[unlikely]] {
        return;
    }
    const auto success = WriteByte(effectiveAddress, x >> 24u) &&
                         WriteByte(effectiveAddress + 2u, x >> 16u) &&
                         WriteByte(effectiveAddress + 4u, x >> 8u) &&
                         WriteByte(effectiveAddress + 6u, x);
    if (!success) [[unlikely]] {
        return;
    }
    ExecuteFinalPrefetchCycle();
}