"""
This module contains inputs for the single operand instructions.
"""
import itertools

from ..status_register_data import ALL_CONDITION_CODE_REGISTERS
from ..types.condition_code import ConditionCode
from ..types.instruction_inputs import \
    SingleInputs, ConditionalInputs
from ..types.sized_instruction_inputs import \
    ByteInstructionInputs, WordInstructionInputs, LongInstructionInputs
from ..types.status_register import StatusRegister


def __create_scc_inputs(condition_code: ConditionCode) -> ByteInstructionInputs:
    return ByteInstructionInputs(inputs=[
        ConditionalInputs(status_register=status_register, condition_code=condition_code, dst=dst)
        for status_register, condition_code, dst in itertools.product(
            ALL_CONDITION_CODE_REGISTERS,
            [condition_code],
            # Long sized value to register operations, memory will use lower 8-bits
            [0x1390_9172])
    ])


NEGX_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    # Check the operation looks like negx
    SingleInputs(dst=0x02),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x02),
    SingleInputs(dst=0x78),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x78),
    # Check that only the lower 8 bits are impacted
    SingleInputs(dst=0xEEBB_AA02),
    # Check the x flag behaviour
    SingleInputs(status_register=StatusRegister(x=False), dst=0x05),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x01),
    # Check the n flag behaviour
    SingleInputs(dst=0x42),
    SingleInputs(dst=0xFF),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x00),
    # Check the z flag behaviour
    # (Cleared if the result is nonzero; unchanged otherwise).
    SingleInputs(status_register=StatusRegister(z=True), dst=0x00),
    SingleInputs(status_register=StatusRegister(z=True), dst=0x01),
    SingleInputs(dst=0x00),
    SingleInputs(dst=0x01),
    # Check the v flag behaviour
    SingleInputs(dst=0x80),
    # Check the carry flag behaviour
    SingleInputs(status_register=StatusRegister(c=False), dst=0x05),
    SingleInputs(status_register=StatusRegister(c=True), dst=0x00),
])

NEGX_WORD_INPUTS = WordInstructionInputs(inputs=[
    # Check the operation looks like negx
    SingleInputs(dst=0x0202),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x0202),
    SingleInputs(dst=0x7879),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x7879),
    # Check that only the lower 16 bits are impacted
    SingleInputs(dst=0xEEBB_AA02),
    # Check the x flag behaviour
    SingleInputs(status_register=StatusRegister(x=False), dst=0x0005),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x0001),
    # Check the n flag behaviour
    SingleInputs(dst=0x3442),
    SingleInputs(dst=0xFFFF),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x0000),
    # Check the z flag behaviour
    # (Cleared if the result is nonzero; unchanged otherwise).
    SingleInputs(status_register=StatusRegister(z=True), dst=0x0000),
    SingleInputs(status_register=StatusRegister(z=True), dst=0x0001),
    SingleInputs(dst=0x0000),
    SingleInputs(dst=0x0001),
    # Check the v flag behaviour
    SingleInputs(dst=0x8000),
    # Check the carry flag behaviour
    SingleInputs(status_register=StatusRegister(c=False), dst=0x0005),
    SingleInputs(status_register=StatusRegister(c=True), dst=0x0000),
])

NEGX_LONG_INPUTS = LongInstructionInputs(inputs=[
    # Check the operation looks like negx
    SingleInputs(dst=0x0303_0202),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x0303_0202),
    SingleInputs(dst=0x2233_7879),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x2233_7879),
    # Check the x flag behaviour
    SingleInputs(status_register=StatusRegister(x=False), dst=0x0000_0005),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x0000_0001),
    # Check the n flag behaviour
    SingleInputs(dst=0x2211_3442),
    SingleInputs(dst=0xFFFF_FFFF),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x0000_0000),
    # Check the z flag behaviour
    # (Cleared if the result is nonzero; unchanged otherwise).
    SingleInputs(status_register=StatusRegister(z=True), dst=0x0000_0000),
    SingleInputs(status_register=StatusRegister(z=True), dst=0x0000_0001),
    SingleInputs(dst=0x0000_0000),
    SingleInputs(dst=0x0000_0001),
    # Check the v flag behaviour
    SingleInputs(dst=0x8000_0000),
    # Check the carry flag behaviour
    SingleInputs(status_register=StatusRegister(c=False), dst=0x0000_0005),
    SingleInputs(status_register=StatusRegister(c=True), dst=0x0000_0000),
])

CLR_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    # Check the operation looks like clr
    SingleInputs(dst=0x99),
    SingleInputs(dst=0x22),
    # Check that only the lower 8 bits are impacted
    SingleInputs(dst=0xACAC_FFCC),
    # Check the x flag doesn't influence the result (and isn't impacted)
    SingleInputs(status_register=StatusRegister(x=False), dst=0xBB),
    SingleInputs(status_register=StatusRegister(x=True), dst=0xBB),
    # Check the n flag behaviour
    SingleInputs(dst=0x00),
    SingleInputs(dst=0x7F),
    SingleInputs(dst=0x80),
    # Check the z flag behaviour
    SingleInputs(status_register=StatusRegister(z=True), dst=0x01),
    SingleInputs(status_register=StatusRegister(z=False), dst=0x01),
    # Check the v flag behaviour (always cleared)
    SingleInputs(status_register=StatusRegister(v=True), dst=0x71),
    # Check the carry flag behaviour (always cleared)
    SingleInputs(status_register=StatusRegister(c=True), dst=0xDD),
])

CLR_WORD_INPUTS = WordInstructionInputs(inputs=[
    # Check the operation looks like clr
    SingleInputs(dst=0x0701),
    SingleInputs(dst=0x9302),
    # Check that only the lower 16 bits are impacted
    SingleInputs(dst=0x4343_6751),
    # Check the x flag doesn't influence the result (and isn't impacted)
    SingleInputs(status_register=StatusRegister(x=False), dst=0x0C06),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x0C06),
    # Check the n flag behaviour
    SingleInputs(dst=0x0000),
    SingleInputs(dst=0x8000),
    SingleInputs(dst=0x7FFF),
    # Check the z flag behaviour
    SingleInputs(status_register=StatusRegister(z=True), dst=0x0E00),
    SingleInputs(status_register=StatusRegister(z=False), dst=0xFEFF),
    # Check the v flag behaviour (always cleared)
    SingleInputs(status_register=StatusRegister(v=True), dst=0x7851),
    # Check the carry flag behaviour (always cleared)
    SingleInputs(status_register=StatusRegister(c=True), dst=0x2321),
])

CLR_LONG_INPUTS = LongInstructionInputs(inputs=[
    # Check the operation looks like clr
    SingleInputs(dst=0x1122_9231),
    SingleInputs(dst=0x8732_2318),
    # Check the x flag doesn't influence the result
    SingleInputs(status_register=StatusRegister(x=False), dst=0x1A05_B005),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x1A05_B005),
    # Check the n flag behaviour
    SingleInputs(dst=0x0000_0000),
    SingleInputs(dst=0x8389_2329),
    SingleInputs(dst=0x7FFF_FFFF),
    # Check the z flag behaviour
    SingleInputs(status_register=StatusRegister(z=True), dst=0x0000_0000),
    SingleInputs(status_register=StatusRegister(z=False), dst=0xFFFF_FFFF),
    # Check the v flag behaviour (always cleared)
    SingleInputs(status_register=StatusRegister(v=True), dst=0x7000_9000),
    # Check the carry flag behaviour (always cleared)
    SingleInputs(status_register=StatusRegister(c=True), dst=0x7000_9000),
])

NEG_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    # Check the operation looks like neg
    SingleInputs(dst=0x03),
    SingleInputs(dst=0x92),
    # Check that only the lower 8 bits are impacted
    SingleInputs(dst=0xAABB_EE75),
    # Check the x flag doesn't influence the result
    SingleInputs(status_register=StatusRegister(x=False), dst=0xAA),
    SingleInputs(status_register=StatusRegister(x=True), dst=0xAA),
    # Check the n flag behaviour
    SingleInputs(dst=0x42),
    SingleInputs(dst=0xFF),
    # Check the z flag behaviour
    SingleInputs(status_register=StatusRegister(z=True), dst=0x00),
    SingleInputs(status_register=StatusRegister(z=False), dst=0x00),
    # Check the v flag behaviour
    SingleInputs(dst=0x80),
    # Check the carry flag behaviour
    SingleInputs(status_register=StatusRegister(c=False), dst=0xDD),
    SingleInputs(status_register=StatusRegister(c=True), dst=0x00),
])

NEG_WORD_INPUTS = WordInstructionInputs(inputs=[
    # Check the operation looks like neg
    SingleInputs(dst=0x0506),
    SingleInputs(dst=0x2389),
    # Check that only the lower 16 bits are impacted
    SingleInputs(dst=0x8958_4033),
    # Check the x flag doesn't influence the result
    SingleInputs(status_register=StatusRegister(x=False), dst=0x0A05),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x0A01),
    # Check the n flag behaviour
    SingleInputs(dst=0x3442),
    SingleInputs(dst=0xFFFF),
    # Check the z flag behaviour
    SingleInputs(status_register=StatusRegister(z=True), dst=0x0000),
    SingleInputs(status_register=StatusRegister(z=False), dst=0x0000),
    # Check the v flag behaviour
    SingleInputs(dst=0x8000),
    # Check the carry flag behaviour
    SingleInputs(status_register=StatusRegister(c=False), dst=0x1205),
    SingleInputs(status_register=StatusRegister(c=True), dst=0x0000),
])

NEG_LONG_INPUTS = LongInstructionInputs(inputs=[
    # Check the operation looks like neg
    SingleInputs(dst=0x1313_1212),
    SingleInputs(dst=0x2323_7789),
    # Check the x flag doesn't influence the result
    SingleInputs(status_register=StatusRegister(x=False), dst=0x0005_0005),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x0005_0005),
    # Check the n flag behaviour
    SingleInputs(dst=0x9389_2329),
    SingleInputs(dst=0xFFFF_FFFF),
    # Check the z flag behaviour
    SingleInputs(status_register=StatusRegister(z=True), dst=0x0000_0000),
    SingleInputs(status_register=StatusRegister(z=False), dst=0x0000_0000),
    # Check the v flag behaviour
    SingleInputs(dst=0x8000_0000),
    # Check the carry flag behaviour
    SingleInputs(status_register=StatusRegister(c=False), dst=0x0000_0009),
    SingleInputs(status_register=StatusRegister(c=True), dst=0x0000_0000),
])

NOT_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    # Check the operation looks like not
    SingleInputs(dst=0xA5),
    SingleInputs(dst=0x29),
    # Check that only the lower 8 bits are impacted
    SingleInputs(dst=0xAACC_EE57),
    # Check the x flag doesn't influence the result (and isn't impacted)
    SingleInputs(status_register=StatusRegister(x=False), dst=0xAA),
    SingleInputs(status_register=StatusRegister(x=True), dst=0xAA),
    # Check the n flag behaviour
    SingleInputs(dst=0x7F),
    SingleInputs(dst=0x80),
    # Check the z flag behaviour
    SingleInputs(status_register=StatusRegister(z=True), dst=0x01),
    SingleInputs(status_register=StatusRegister(z=False), dst=0xFF),
    # Check the v flag behaviour (always cleared)
    SingleInputs(status_register=StatusRegister(v=True), dst=0x71),
    # Check the carry flag behaviour (always cleared)
    SingleInputs(status_register=StatusRegister(c=True), dst=0xDD),
])

NOT_WORD_INPUTS = WordInstructionInputs(inputs=[
    # Check the operation looks like not
    SingleInputs(dst=0x0107),
    SingleInputs(dst=0x6721),
    # Check that only the lower 16 bits are impacted
    SingleInputs(dst=0x3201_4443),
    # Check the x flag doesn't influence the result (and isn't impacted)
    SingleInputs(status_register=StatusRegister(x=False), dst=0x0B05),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x0B05),
    # Check the n flag behaviour
    SingleInputs(dst=0x8000),
    SingleInputs(dst=0x7FFF),
    # Check the z flag behaviour
    SingleInputs(status_register=StatusRegister(z=True), dst=0x0000),
    SingleInputs(status_register=StatusRegister(z=False), dst=0xFFFF),
    # Check the v flag behaviour (always cleared)
    SingleInputs(status_register=StatusRegister(v=True), dst=0x1234),
    # Check the carry flag behaviour (always cleared)
    SingleInputs(status_register=StatusRegister(c=True), dst=0x1234),
])

NOT_LONG_INPUTS = LongInstructionInputs(inputs=[
    # Check the operation looks like not
    SingleInputs(dst=0x7843_4391),
    SingleInputs(dst=0x1321_3431),
    # Check the x flag doesn't influence the result
    SingleInputs(status_register=StatusRegister(x=False), dst=0x1105_1005),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x1105_1005),
    # Check the n flag behaviour
    SingleInputs(dst=0x8389_2329),
    SingleInputs(dst=0x7FFF_FFFF),
    # Check the z flag behaviour
    SingleInputs(status_register=StatusRegister(z=True), dst=0x0000_0000),
    SingleInputs(status_register=StatusRegister(z=False), dst=0xFFFF_FFFF),
    # Check the v flag behaviour (always cleared)
    SingleInputs(status_register=StatusRegister(v=True), dst=0x7000_8000),
    # Check the carry flag behaviour (always cleared)
    SingleInputs(status_register=StatusRegister(c=True), dst=0x7000_8000),
])

NBCD_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    # Check the operation looks like nbcd
    SingleInputs(dst=0x22),
    SingleInputs(dst=0x92),
    # Check that only the lower 8 bits are impacted
    SingleInputs(dst=0xAACC_EE57),
    # Check the x flag influences there result
    SingleInputs(status_register=StatusRegister(x=False), dst=0x15),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x15),
    # Check the x flag is influenced by carry out
    SingleInputs(status_register=StatusRegister(x=False), dst=0x01),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x00),
    # Check the n flag behaviour
    SingleInputs(status_register=StatusRegister(n=False), dst=0x01),
    SingleInputs(status_register=StatusRegister(n=True), dst=0x00),
    # Check the z flag behaviour
    # (Cleared if the result is nonzero; unchanged otherwise).
    SingleInputs(status_register=StatusRegister(z=True), dst=0x00),
    SingleInputs(status_register=StatusRegister(z=True), dst=0x01),
    SingleInputs(status_register=StatusRegister(z=False), dst=0x00),
    SingleInputs(status_register=StatusRegister(z=False), dst=0x01),
    # Check the v flag behaviour
    SingleInputs(status_register=StatusRegister(v=True), dst=0x99),
    SingleInputs(status_register=StatusRegister(v=False), dst=0x52),
    # Check the carry flag behaviour
    SingleInputs(status_register=StatusRegister(c=False), dst=0xDD),
    SingleInputs(status_register=StatusRegister(c=True), dst=0x00),
])

TAS_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    # Check x flag behaviour
    SingleInputs(status_register=StatusRegister(x=False), dst=0x7F),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x7F),
    # Check n flag behaviour
    SingleInputs(status_register=StatusRegister(n=False), dst=0x80),
    SingleInputs(status_register=StatusRegister(n=True), dst=0x00),
    # Check z flag behaviour
    SingleInputs(status_register=StatusRegister(z=False), dst=0x00),
    SingleInputs(status_register=StatusRegister(z=True), dst=0x01),
    # Check v and c flags are cleared
    SingleInputs(status_register=StatusRegister(v=True, c=True), dst=0x00),
    SingleInputs(status_register=StatusRegister(v=True, c=True), dst=0x7F),
])

TST_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    # Check that only the lower 8 bits are used
    SingleInputs(dst=0xFFFF_FF40),
    SingleInputs(dst=0x0000_0080),
    # Check the x flag isn't affected
    SingleInputs(status_register=StatusRegister(x=False), dst=0x80),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x80),
    # Check the n flag behaviour
    SingleInputs(status_register=StatusRegister(n=False), dst=0x80),
    SingleInputs(status_register=StatusRegister(n=True), dst=0x40),
    # Check the z flag behaviour
    SingleInputs(status_register=StatusRegister(z=True), dst=0x00),
    SingleInputs(status_register=StatusRegister(z=False), dst=0x01),
    # Check the v flag behaviour (always reset)
    SingleInputs(status_register=StatusRegister(v=True), dst=0x18),
    SingleInputs(status_register=StatusRegister(v=False), dst=0x81),
    # Check the carry flag behaviour (always reset)
    SingleInputs(status_register=StatusRegister(c=True), dst=0x18),
    SingleInputs(status_register=StatusRegister(c=False), dst=0x81),
])

TST_WORD_INPUTS = WordInstructionInputs(inputs=[
    # Check that only the lower 16 bits are used
    SingleInputs(dst=0xFFFF_4000),
    SingleInputs(dst=0x0000_8000),
    # Check the x flag isn't affected
    SingleInputs(status_register=StatusRegister(x=False), dst=0x8000),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x8000),
    # Check the n flag behaviour
    SingleInputs(status_register=StatusRegister(n=False), dst=0x8000),
    SingleInputs(status_register=StatusRegister(n=True), dst=0x4000),
    # Check the z flag behaviour
    SingleInputs(status_register=StatusRegister(z=True), dst=0x0000),
    SingleInputs(status_register=StatusRegister(z=False), dst=0x0001),
    # Check the v flag behaviour (always reset)
    SingleInputs(status_register=StatusRegister(v=True), dst=0x1818),
    SingleInputs(status_register=StatusRegister(v=False), dst=0x8181),
    # Check the carry flag behaviour (always reset)
    SingleInputs(status_register=StatusRegister(c=True), dst=0x1818),
    SingleInputs(status_register=StatusRegister(c=False), dst=0x8181),
])

TST_LONG_INPUTS = LongInstructionInputs(inputs=[
    # Check the x flag isn't affected
    SingleInputs(status_register=StatusRegister(x=False), dst=0x8000_0000),
    SingleInputs(status_register=StatusRegister(x=True), dst=0x8000_0000),
    # Check the n flag behaviour
    SingleInputs(status_register=StatusRegister(n=False), dst=0x8000_0000),
    SingleInputs(status_register=StatusRegister(n=True), dst=0x4000_0000),
    # Check the z flag behaviour
    SingleInputs(status_register=StatusRegister(z=True), dst=0x0000_0000),
    SingleInputs(status_register=StatusRegister(z=False), dst=0x0001_0000),
    # Check the v flag behaviour (always reset)
    SingleInputs(status_register=StatusRegister(v=True), dst=0x1818_1818),
    SingleInputs(status_register=StatusRegister(v=False), dst=0x8181_8181),
    # Check the carry flag behaviour (always reset)
    SingleInputs(status_register=StatusRegister(c=True), dst=0x1818_1818),
    SingleInputs(status_register=StatusRegister(c=False), dst=0x8181_8181),
])

ST_INPUTS = __create_scc_inputs(ConditionCode.T)
SF_INPUTS = __create_scc_inputs(ConditionCode.F)
SHI_INPUTS = __create_scc_inputs(ConditionCode.HI)
SLS_INPUTS = __create_scc_inputs(ConditionCode.LS)
SCC_INPUTS = __create_scc_inputs(ConditionCode.CC)
SCS_INPUTS = __create_scc_inputs(ConditionCode.CS)
SNE_INPUTS = __create_scc_inputs(ConditionCode.NE)
SEQ_INPUTS = __create_scc_inputs(ConditionCode.EQ)
SVC_INPUTS = __create_scc_inputs(ConditionCode.VC)
SVS_INPUTS = __create_scc_inputs(ConditionCode.VS)
SPL_INPUTS = __create_scc_inputs(ConditionCode.PL)
SMI_INPUTS = __create_scc_inputs(ConditionCode.MI)
SGE_INPUTS = __create_scc_inputs(ConditionCode.GE)
SLT_INPUTS = __create_scc_inputs(ConditionCode.LT)
SGT_INPUTS = __create_scc_inputs(ConditionCode.GT)
SLE_INPUTS = __create_scc_inputs(ConditionCode.LE)
