import itertools

from ..types.address_modes import \
    IndexRegisterType, \
    IndexRegisterSize, \
    IndexRegister, \
    Null, \
    DataRegister, \
    AddressRegister, \
    AddressIndirect, \
    AddressIncrement, \
    StackIncrement, \
    AddressDecrement, \
    StackDecrement, \
    AddressDisplacement, \
    AddressIndex, \
    Short, \
    Long, \
    PcDisplacement, \
    PcIndex, \
    Immediate, \
    BitwiseImmediate, \
    QuickImmediate, \
    DecrementAndBranch, \
    BranchByte, \
    BranchWord, \
    BranchSubroutineByte, \
    BranchSubroutineWord, \
    StatusRegisterMode, \
    ConditionCodeRegisterMode

__ADDRESS_REGISTER_VALUES = [0x1_0000, 0x2_0000]
__ADDRESS_REGISTER_VALUES_ALTERNATE = [0x3_0000, 0x4_0000]
__WORD_DISPLACEMENTS = [-400, 200, 4000]
__BYTE_DISPLACEMENTS = [-126, 70, 120]
__INDEX_REGISTER_TYPES = [IndexRegisterType.DATA_REGISTER, IndexRegisterType.ADDRESS_REGISTER]
__INDEX_REGISTER_SIZES = [IndexRegisterSize.WORD, IndexRegisterSize.LONG]
__INDEX_REGISTER_VALUES = [0x000CC7000, 0x00CC8000]
__INDEX_REGISTERS = [
    IndexRegister(type=t, size=size, number=n, value=v)
    for t, size, n, v in itertools.product(
        __INDEX_REGISTER_TYPES,
        __INDEX_REGISTER_SIZES,
        [1, 3],
        __INDEX_REGISTER_VALUES
    )
]
__SHORT_ADDRESSES = [0x6000, 0x8CCC]
__LONG_ADDRESSES = [0x8CCC, 0x1_0000]
__DECREMENT_AND_BRANCH_DISPLACEMENTS = [0x66, -0x78, -0x1004, 0x1070]
__BYTE_BRANCH_DISPLACEMENTS = [0x66, -0x78]
__WORD_BRANCH_DISPLACEMENTS = [-0x1004, 0x1070]

PCS = [0x2000]
NULLS = [Null()]
DATA_REGISTERS = [DataRegister(number=x) for x in [0, 3, 6, 7]]
DATA_REGISTERS_REDUCED = [DataRegister(number=x) for x in [0, 7]]
ADDRESS_REGISTERS = [AddressRegister(number=x) for x in [1, 4, 5, 7]]
ADDRESS_INDIRECTS = [
    AddressIndirect(number=n, value=v)
    for n, v in itertools.product([2, 5], __ADDRESS_REGISTER_VALUES)
]
ADDRESS_INCREMENTS = [
    AddressIncrement(number=n, value=v)
    for n, v in itertools.product([0, 6], __ADDRESS_REGISTER_VALUES)
]
ADDRESS_INCREMENTS_ALTERNATE = [
    AddressIncrement(number=n, value=v)
    for n, v in itertools.product([5, 1], __ADDRESS_REGISTER_VALUES_ALTERNATE)
]
STACK_INCREMENTS = [
    StackIncrement(value=v) for v in __ADDRESS_REGISTER_VALUES
]
ADDRESS_DECREMENTS = [
    AddressDecrement(number=n, value=v)
    for n, v in itertools.product([3, 6], __ADDRESS_REGISTER_VALUES)
]
ADDRESS_DECREMENTS_ALTERNATE = [
    AddressDecrement(number=n, value=v)
    for n, v in itertools.product([2, 4], __ADDRESS_REGISTER_VALUES_ALTERNATE)
]
STACK_DECREMENTS = [StackDecrement(value=v) for v in __ADDRESS_REGISTER_VALUES]
ADDRESS_DISPLACEMENTS = [
    AddressDisplacement(number=n, value=v, displacement=displacement)
    for n, v, displacement in itertools.product(
        [1, 7],
        __ADDRESS_REGISTER_VALUES,
        __WORD_DISPLACEMENTS
    )
]
ADDRESS_INDEXES = [
    AddressIndex(number=n, value=v, displacement=displacement, index=index)
    for n, v, displacement, index in itertools.product(
        [5, 6],
        __ADDRESS_REGISTER_VALUES,
        __BYTE_DISPLACEMENTS,
        __INDEX_REGISTERS
    )
    if index.type == IndexRegisterType.DATA_REGISTER or n != index.number
]
SHORTS = [Short(value=v) for v in __SHORT_ADDRESSES]
LONGS = [Long(value=v) for v in __SHORT_ADDRESSES]
PC_DISPLACEMENTS = [PcDisplacement(displacement=v) for v in __WORD_DISPLACEMENTS]
PC_INDEXES = [
    PcIndex(displacement=displacement, index=index)
    for displacement, index in itertools.product(__BYTE_DISPLACEMENTS, __INDEX_REGISTERS)
]
IMMEDIATES = [Immediate()]
BITWISE_IMMEDIATES = [BitwiseImmediate()]
QUICK_IMMEDIATES = [QuickImmediate()]
WORD_DECREMENT_AND_BRANCHES = [
    DecrementAndBranch(number=n, displacement=d)
    for n, d in itertools.product([3, 6], __DECREMENT_AND_BRANCH_DISPLACEMENTS)
]
BYTE_BRANCHES = [BranchByte(displacement=d) for d in __BYTE_BRANCH_DISPLACEMENTS]
WORD_BRANCHES = [BranchWord(displacement=d) for d in __WORD_BRANCH_DISPLACEMENTS]
BYTE_SUBROUTINE_BRANCHES = [
    BranchSubroutineByte(value=v, displacement=d)
    for v, d in itertools.product(__ADDRESS_REGISTER_VALUES, __BYTE_BRANCH_DISPLACEMENTS)
]
WORD_SUBROUTINE_BRANCHES = [
    BranchSubroutineWord(value=v, displacement=d)
    for v, d in itertools.product(__ADDRESS_REGISTER_VALUES, __BYTE_BRANCH_DISPLACEMENTS)
]
CONDITION_CODE_REGISTERS = [ConditionCodeRegisterMode()]
STATUS_REGISTERS = [StatusRegisterMode()]
