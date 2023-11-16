"""
This module contains inputs for the shift rotate right instructions.
"""

from ..types.instruction_inputs import \
    BinaryInputs
from ..types.sized_instruction_inputs import \
    ByteInstructionInputs, WordInstructionInputs, LongInstructionInputs

from ..types.status_register import StatusRegister

ASR_BYTE_COUNT_INPUTS = ByteInstructionInputs(inputs=[
    # Check that the operation looks like arithmetic shift right
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(src=1, dst=0x40),
    BinaryInputs(src=1, dst=0xFFFF_FF08),
    # Different shift values
    BinaryInputs(src=3, dst=0xCF),
    BinaryInputs(src=4, dst=0x2D),
    BinaryInputs(src=7, dst=0xA5),
    # Check the x flag behaviour
    BinaryInputs(src=2, dst=0x00),
    BinaryInputs(src=2, dst=0x02),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0),
    BinaryInputs(src=3, dst=0x70),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x7F),
    # Check the overflow flag behaviour (set if MSB changes)
    BinaryInputs(src=8, dst=0x80),
    BinaryInputs(src=8, dst=0x7E),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x00),
    BinaryInputs(src=1, dst=0x01)
])

ASR_WORD_COUNT_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like arithmetic shift right
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4000),
    BinaryInputs(src=1, dst=0xFFFF_4040),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD),
    BinaryInputs(src=4, dst=0xD4CC),
    BinaryInputs(src=7, dst=0xA522),
    # Check the x flag behaviour
    BinaryInputs(src=2, dst=0x0000),
    BinaryInputs(src=2, dst=0x0002),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0EF),
    BinaryInputs(src=3, dst=0x70EF),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x00EF),
    # Check the overflow flag behaviour (set if MSB changes)
    BinaryInputs(src=8, dst=0x8000),
    BinaryInputs(src=8, dst=0x7E00),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x0000),
    BinaryInputs(src=1, dst=0x0001)
])

ASR_LONG_COUNT_INPUTS = LongInstructionInputs(inputs=[
    # Check that the operation looks like arithmetic shift right
    BinaryInputs(src=1, dst=0x8000_0000),
    BinaryInputs(src=1, dst=0x4000_0000),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD_A55A),
    BinaryInputs(src=4, dst=0xD4CC_B55A),
    BinaryInputs(src=7, dst=0xA522_A55A),
    # Check the x flag behaviour
    BinaryInputs(src=2, dst=0x4040_0000),
    BinaryInputs(src=2, dst=0x4040_0002),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0FE_CDCD),
    BinaryInputs(src=3, dst=0x70FF_CDCD),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x0000_00FF),
    # Check the overflow flag behaviour (set if MSB changes)
    BinaryInputs(src=8, dst=0x8000_CDCD),
    BinaryInputs(src=8, dst=0x7E00_CDCD),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x0000_0000),
    BinaryInputs(src=1, dst=0x0000_0001)
])

ASR_BYTE_REGISTER_INPUTS = ByteInstructionInputs(inputs=[
    # Check that the operation looks like arithmetic shift right
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(src=1, dst=0x40),
    BinaryInputs(src=3, dst=0xFFFF_FF4E),
    # Different shift values
    BinaryInputs(src=3, dst=0xCE),
    BinaryInputs(src=4, dst=0xD2),
    BinaryInputs(src=7, dst=0xA6),
    BinaryInputs(src=900, dst=0xD2),
    BinaryInputs(src=803, dst=0xA6),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x81),
    BinaryInputs(src=2, dst=0x00),
    BinaryInputs(src=2, dst=0x02),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0),
    BinaryInputs(src=3, dst=0x70),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x7F),
    # Check the overflow flag behaviour (set if MSB changes)
    BinaryInputs(src=8, dst=0x80),
    BinaryInputs(src=8, dst=0x7E),
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=True), src=0, dst=0xEE),
    BinaryInputs(src=1, dst=0x00),
    BinaryInputs(src=1, dst=0x01),
    BinaryInputs(src=2, dst=0x02)
])

ASR_WORD_REGISTER_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like arithmetic shift right
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4000),
    BinaryInputs(src=3, dst=0xFFFF_4EFF),
    # Different shift values
    BinaryInputs(src=3, dst=0xCECD),
    BinaryInputs(src=4, dst=0xD3CD),
    BinaryInputs(src=7, dst=0xA51D),
    BinaryInputs(src=900, dst=0xD3CD),
    BinaryInputs(src=803, dst=0xA5CD),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x8001),
    BinaryInputs(src=2, dst=0x7F00),
    BinaryInputs(src=2, dst=0x7F02),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0CD),
    BinaryInputs(src=3, dst=0x70CD),
    # Check the zero flag behaviour
    BinaryInputs(src=15, dst=0x7FFF),
    # Check the overflow flag behaviour (set if MSB changes)
    BinaryInputs(src=8, dst=0x8000),
    BinaryInputs(src=8, dst=0x7E00),
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=True), src=0, dst=0x11EE),
    BinaryInputs(src=1, dst=0x7FFF_0000),
    BinaryInputs(src=1, dst=0x7FFF_0001),
    BinaryInputs(src=2, dst=0x7FFF_0002)
])

ASR_LONG_REGISTER_INPUTS = LongInstructionInputs(inputs=[
    # Check that the operation looks like arithmetic shift right
    BinaryInputs(src=1, dst=0x8000_0000),
    BinaryInputs(src=1, dst=0x4000_0000),
    BinaryInputs(src=3, dst=0xFFFF_4EFF),
    # Different shift values
    BinaryInputs(src=3, dst=0xCECD_ACBC),
    BinaryInputs(src=4, dst=0xD3CD_ACBC),
    BinaryInputs(src=7, dst=0xA51D_BCBC),
    BinaryInputs(src=457, dst=0xD3CD_BCBC),
    BinaryInputs(src=1666, dst=0xA5CD_BCBC),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x8000_0001),
    BinaryInputs(src=2, dst=0x7F00_0000),
    BinaryInputs(src=2, dst=0x7F00_0002),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0CD_FECD),
    BinaryInputs(src=3, dst=0x70CD_FECD),
    # Check the zero flag behaviour
    BinaryInputs(src=31, dst=0x7FFF_FFFF),
    # Check the overflow flag behaviour (set if MSB changes)
    BinaryInputs(src=17, dst=0x8000_0000),
    BinaryInputs(src=17, dst=0x7E00_0000),
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=True), src=0, dst=0xFFCC_CCEE),
    BinaryInputs(src=1, dst=0x7FFF_0000),
    BinaryInputs(src=1, dst=0x7FFF_0001),
    BinaryInputs(src=2, dst=0x7FFF_0002)
])

# The shift for these operations is _always_ 1.
ASR_WORD_MEMORY_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like arithmetic shift right
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4000),
    # Check the x flag behaviour
    BinaryInputs(src=1, dst=0x7F00),
    BinaryInputs(src=1, dst=0x7F01),
    # Check the negative flag behaviour
    BinaryInputs(src=1, dst=0xC0CD),
    BinaryInputs(src=1, dst=0x70CD),
    # Check the zero flag behaviour
    BinaryInputs(src=1, dst=0x0001),
    # Check the overflow flag behaviour (set if MSB changes)
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x7E00),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x0A00),
    BinaryInputs(src=1, dst=0x0A01),
])

LSR_BYTE_COUNT_INPUTS = ByteInstructionInputs(inputs=[
    # Check that the operation looks like logical shift right
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(src=1, dst=0x40),
    BinaryInputs(src=1, dst=0xFFFF_FF08),
    # Different shift values
    BinaryInputs(src=3, dst=0xEC),
    BinaryInputs(src=4, dst=0x7F),
    BinaryInputs(src=7, dst=0xC9),
    # Check the x flag behaviour
    BinaryInputs(src=2, dst=0x00),
    BinaryInputs(src=3, dst=0x04),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0),
    BinaryInputs(src=3, dst=0x70),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0xFF),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x80),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x00),
    BinaryInputs(src=1, dst=0x01)
])

LSR_WORD_COUNT_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like logical shift right
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4000),
    BinaryInputs(src=1, dst=0xFFFF_4040),
    # Different shift values
    BinaryInputs(src=3, dst=0xCE99),
    BinaryInputs(src=4, dst=0xD56C),
    BinaryInputs(src=3, dst=0xA322),
    # Check the x flag behaviour
    BinaryInputs(src=2, dst=0x0000),
    BinaryInputs(src=2, dst=0x0002),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0FF),
    BinaryInputs(src=3, dst=0x70FF),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x00FF),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x0000),
    BinaryInputs(src=1, dst=0x0001)
])

LSR_LONG_COUNT_INPUTS = LongInstructionInputs(inputs=[
    # Check that the operation looks like logical shift right
    BinaryInputs(src=1, dst=0x8000_0000),
    BinaryInputs(src=1, dst=0x4000_0000),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEEE_5AA5),
    BinaryInputs(src=4, dst=0xD3DD_5AA5),
    BinaryInputs(src=7, dst=0xA5FF_5AA5),
    # Check the x flag behaviour
    BinaryInputs(src=2, dst=0x4040_0000),
    BinaryInputs(src=2, dst=0x4040_0002),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0FF_DCDC),
    BinaryInputs(src=3, dst=0x70FF_DCDC),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x0000_00FF),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x8000_CDCD),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00_CDCD),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x0000_0000),
    BinaryInputs(src=1, dst=0x0000_0001)
])

LSR_BYTE_REGISTER_INPUTS = ByteInstructionInputs(inputs=[
    # Check that the operation looks like logical shift right
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(src=1, dst=0x40),
    BinaryInputs(src=3, dst=0xFFFF_FF4E),
    # Different shift values
    BinaryInputs(src=3, dst=0xCE),
    BinaryInputs(src=4, dst=0xD4),
    BinaryInputs(src=7, dst=0xA5),
    BinaryInputs(src=901, dst=0xD4),
    BinaryInputs(src=802, dst=0xA5),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x81),
    BinaryInputs(src=2, dst=0x00),
    BinaryInputs(src=2, dst=0x02),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0),
    BinaryInputs(src=3, dst=0x70),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0xFF),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x80),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E),
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=True), src=0, dst=0xEE),
    BinaryInputs(src=1, dst=0x00),
    BinaryInputs(src=1, dst=0x01),
    BinaryInputs(src=2, dst=0x02)
])

LSR_WORD_REGISTER_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like logical shift right
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4000),
    BinaryInputs(src=3, dst=0xFFFF_4EFF),
    # Different shift values
    BinaryInputs(src=3, dst=0xCABD),
    BinaryInputs(src=4, dst=0xDD3D),
    BinaryInputs(src=7, dst=0xAC5D),
    BinaryInputs(src=900, dst=0xDC3D),
    BinaryInputs(src=803, dst=0xAB5D),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x8001),
    BinaryInputs(src=2, dst=0x7F00),
    BinaryInputs(src=2, dst=0x7F02),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0CD),
    BinaryInputs(src=3, dst=0x70CD),
    # Check the zero flag behaviour
    BinaryInputs(src=15, dst=0x7FFF),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00),
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=True), src=0, dst=0xCCEE),
    BinaryInputs(src=1, dst=0x7F00_FF00),
    BinaryInputs(src=1, dst=0x7F00_FF01),
    BinaryInputs(src=2, dst=0x7F00_FF02)
])

LSR_LONG_REGISTER_INPUTS = LongInstructionInputs(inputs=[
    # Check that the operation looks like logical shift right
    BinaryInputs(src=1, dst=0x8000_0000),
    BinaryInputs(src=1, dst=0x4000_0000),
    BinaryInputs(src=3, dst=0xFFFF_4EFF),
    # Different shift values
    BinaryInputs(src=3, dst=0xCECD_BCBC),
    BinaryInputs(src=4, dst=0xD3CD_ACBC),
    BinaryInputs(src=7, dst=0xA51D_BCBC),
    BinaryInputs(src=798, dst=0xD3CD_BCBC),
    BinaryInputs(src=6661, dst=0xA5CD_BCBC),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x8000_0001),
    BinaryInputs(src=2, dst=0x7F00_0000),
    BinaryInputs(src=2, dst=0x7F00_0002),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0CD_FECD),
    BinaryInputs(src=3, dst=0x70CD_FECD),
    # Check the zero flag behaviour
    BinaryInputs(src=32, dst=0xFFFF_FFFF),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=17, dst=0x8000_0000),
    BinaryInputs(status_register=StatusRegister(v=True), src=17, dst=0x7E00_0000),
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=True), src=0, dst=0xCCDD_AAEE),
    BinaryInputs(src=1, dst=0x7FFF_0000),
    BinaryInputs(src=1, dst=0x7FFF_0001),
    BinaryInputs(src=2, dst=0x7FFF_0002)
])


# The shift for these operations is _always_ 1.
LSR_WORD_MEMORY_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like logical shift right
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4000),
    # Check the x flag behaviour
    BinaryInputs(src=1, dst=0x7F00),
    BinaryInputs(src=1, dst=0x7F01),
    # Check the negative flag behaviour
    BinaryInputs(src=1, dst=0xC0CD),
    BinaryInputs(src=1, dst=0x70CD),
    # Check the zero flag behaviour
    BinaryInputs(src=1, dst=0x0001),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x7E00),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x0A00),
    BinaryInputs(src=1, dst=0x0A01),
])

ROXR_BYTE_COUNT_INPUTS = ByteInstructionInputs(inputs=[
    # Check that the operation looks like rotate extended right
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x40),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xFFFF_FF08),
    # Different shift values
    BinaryInputs(src=3, dst=0xCE),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xE3),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA5),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x00),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x02),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0),
    BinaryInputs(src=1, dst=0xC0),
    BinaryInputs(src=1, dst=0x70),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x00),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x80),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x00),
    BinaryInputs(src=1, dst=0x01)
])

ROXR_WORD_COUNT_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like rotate extended right
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4000),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xFFFF_4040),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD4CC),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA522),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x0000),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x0002),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0FF),
    BinaryInputs(src=3, dst=0xC0FF),
    BinaryInputs(src=3, dst=0x70FF),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x0000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x0000),
    BinaryInputs(src=1, dst=0x0001)
])

ROXR_LONG_COUNT_INPUTS = LongInstructionInputs(inputs=[
    # Check that the operation looks like rotate extended right
    BinaryInputs(src=1, dst=0x8000_0000),
    BinaryInputs(src=1, dst=0x4000_0000),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4000_0000),
    # Different shift values
    BinaryInputs(src=3, dst=0xCECC_AA5A),
    BinaryInputs(src=5, dst=0xD3DD_A55A),
    BinaryInputs(src=7, dst=0xA522_A5AA),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xE3CB_A55A),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA522_A55A),
    # Check the x flag behaviour
    BinaryInputs(src=2, dst=0x4040_0000),
    BinaryInputs(src=2, dst=0x4040_0002),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0FE_CDCD),
    BinaryInputs(src=3, dst=0xC0FE_CDCD),
    BinaryInputs(src=3, dst=0x70FF_CDCD),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x0000_0000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x8000_CDCD),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00_CDCD),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x0000_0000),
    BinaryInputs(src=1, dst=0x0000_0001)
])

ROXR_BYTE_REGISTER_INPUTS = ByteInstructionInputs(inputs=[
    # Check that the operation looks like rotate extended right
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x40),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xFFFF_FF08),
    # Different shift values
    BinaryInputs(src=3, dst=0xCE),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xE3),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA5),
    BinaryInputs(src=803, dst=0xE3),
    BinaryInputs(src=696, dst=0xA5),
    # Check the x flag behaviour
    BinaryInputs(src=0, dst=0x01),
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x01),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x00),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x02),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0),
    BinaryInputs(src=0, dst=0xC0),
    BinaryInputs(src=1, dst=0xC0),
    BinaryInputs(src=1, dst=0x70),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x00),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x80),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E),
    # Check the carry flag behaviour (when shift is zero then carry is set to x)
    BinaryInputs(status_register=StatusRegister(x=True, c=False), src=0, dst=0x01),
    BinaryInputs(status_register=StatusRegister(x=False, c=True), src=0, dst=0x01),
    BinaryInputs(src=1, dst=0x00),
    BinaryInputs(src=1, dst=0x01)
])

ROXR_WORD_REGISTER_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like rotate extended right
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4000),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xFFFF_4040),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD4CC),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA522),
    BinaryInputs(src=777, dst=0xD4CC),
    BinaryInputs(src=779, dst=0xA522),
    # Check the x flag behaviour
    BinaryInputs(src=0, dst=0x0001),
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x0001),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x0000),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x0002),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0FF),
    BinaryInputs(src=0, dst=0xC0DF),
    BinaryInputs(src=3, dst=0xC0DF),
    BinaryInputs(src=3, dst=0x70EF),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x0000),
    BinaryInputs(src=16, dst=0x0000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00),
    # Check the carry flag behaviour (when shift is zero then carry is set to x)
    BinaryInputs(status_register=StatusRegister(x=True, c=False), src=0, dst=0x0001),
    BinaryInputs(status_register=StatusRegister(x=False, c=True), src=0, dst=0x0001),
    BinaryInputs(src=1, dst=0x0000),
    BinaryInputs(src=1, dst=0x0001)
])

ROXR_LONG_REGISTER_INPUTS = LongInstructionInputs(inputs=[
    # Check that the operation looks like rotate extended right
    BinaryInputs(src=1, dst=0x8000_0000),
    BinaryInputs(src=1, dst=0x4000_0000),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4000_0000),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD_A55A),
    BinaryInputs(src=4, dst=0xD4CC_B55A),
    BinaryInputs(src=7, dst=0xA522_A55A),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD4CC_B55A),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA522_A55A),
    BinaryInputs(src=8763, dst=0xD4CC_B55A),
    BinaryInputs(src=2320, dst=0xA522_A55A),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0xD4CC_B55A),
    BinaryInputs(src=2, dst=0x4040_0000),
    BinaryInputs(src=2, dst=0x4040_0002),
    # Check the negative flag behaviour
    BinaryInputs(src=0, dst=0x0000_0001),
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x0000_0001),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0FE_CDCD),
    BinaryInputs(src=3, dst=0xC0FE_CDCD),
    BinaryInputs(src=3, dst=0x70FF_CDCD),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x0000_0000),
    BinaryInputs(src=32, dst=0x0000_00000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x8000_CDCD),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00_CDCD),
    # Check the carry flag behaviour (when shift is zero then carry is set to x)
    BinaryInputs(status_register=StatusRegister(x=True, c=False), src=0, dst=0x0000_0001),
    BinaryInputs(status_register=StatusRegister(x=False, c=True), src=0, dst=0x0000_0001),
    BinaryInputs(src=1, dst=0x0000_0000),
    BinaryInputs(src=1, dst=0x0000_0001)
])

# The shift for these operations is _always_ 1.
ROXR_WORD_MEMORY_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like rotate extended right
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4000),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4000),
    # Check the x flag behaviour
    BinaryInputs(src=1, dst=0x0000),
    BinaryInputs(src=1, dst=0x0001),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xCDCD),
    BinaryInputs(src=1, dst=0xCDCD),
    # Check the zero flag behaviour
    BinaryInputs(src=1, dst=0x0000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x7E00),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x0000),
    BinaryInputs(src=1, dst=0x0001)
])


ROR_BYTE_COUNT_INPUTS = ByteInstructionInputs(inputs=[
    # Check that the operation looks like rotate right
    BinaryInputs(src=1, dst=0x83),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x42),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xFFFF_FF18),
    # Different shift values
    BinaryInputs(src=3, dst=0xCE),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xE3),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA5),
    # Check the x flag behaviour (unchanged)
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x00),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x02),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC1),
    BinaryInputs(src=1, dst=0xC1),
    BinaryInputs(src=1, dst=0x70),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x00),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x80),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x00),
    BinaryInputs(src=1, dst=0x01)
])

ROR_WORD_COUNT_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like rotate right
    BinaryInputs(src=1, dst=0x8102),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4030),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xFFFF_4340),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD4CC),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA522),
    # Check the x flag behaviour (unchanged)
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x0000),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x0002),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0FF),
    BinaryInputs(src=3, dst=0xC0FF),
    BinaryInputs(src=3, dst=0x70F0),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x0000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x0000),
    BinaryInputs(src=1, dst=0x0001)
])

ROR_LONG_COUNT_INPUTS = LongInstructionInputs(inputs=[
    # Check that the operation looks like rotate right
    BinaryInputs(src=1, dst=0x8000_0002),
    BinaryInputs(src=1, dst=0x4000_0002),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4000_0002),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD_A55A),
    BinaryInputs(src=4, dst=0xD4CC_B55A),
    BinaryInputs(src=7, dst=0xA522_A55A),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD4CC_B55A),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA522_A55A),
    # Check the x flag behaviour (unchanged)
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x4040_0000),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x4040_0002),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0FE_CDCD),
    BinaryInputs(src=3, dst=0xC0FE_CDCD),
    BinaryInputs(src=3, dst=0x70FF_CDCD),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x0000_0000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x8000_CDCD),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00_CDCD),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x0000_0000),
    BinaryInputs(src=1, dst=0x0000_0001)
])

ROR_BYTE_REGISTER_INPUTS = ByteInstructionInputs(inputs=[
    # Check that the operation looks like rotate right
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x40),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xFFFF_FF08),
    # Different shift values
    BinaryInputs(src=3, dst=0xCE),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xE3),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xB5),
    BinaryInputs(src=803, dst=0xE3),
    BinaryInputs(src=696, dst=0xB5),
    # Check the x flag behaviour (unchanged)
    BinaryInputs(src=0, dst=0x01),
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x01),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x00),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x02),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0),
    BinaryInputs(src=0, dst=0xC0),
    BinaryInputs(src=1, dst=0xC0),
    BinaryInputs(src=1, dst=0x70),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x00),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x80),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E),
    # Check the carry flag behaviour (when shift is zero then carry is set to x)
    BinaryInputs(status_register=StatusRegister(x=True, c=False), src=0, dst=0x01),
    BinaryInputs(status_register=StatusRegister(x=False, c=True), src=0, dst=0x01),
    BinaryInputs(src=1, dst=0x00),
    BinaryInputs(src=1, dst=0x01)
])

ROR_WORD_REGISTER_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like rotate right
    BinaryInputs(src=1, dst=0x8010),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4010),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xFFFF_4040),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD4CC),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA522),
    BinaryInputs(src=777, dst=0xD4CC),
    BinaryInputs(src=779, dst=0xA522),
    # Check the x flag behaviour (unchanged)
    BinaryInputs(src=0, dst=0x0001),
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x0001),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x0000),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x0002),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0EF),
    BinaryInputs(src=0, dst=0xC0EF),
    BinaryInputs(src=3, dst=0xC0EF),
    BinaryInputs(src=3, dst=0x70E0),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x0000),
    BinaryInputs(src=16, dst=0x0000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00),
    # Check the carry flag behaviour (when shift is zero then carry is set to x)
    BinaryInputs(status_register=StatusRegister(x=True, c=False), src=0, dst=0x0001),
    BinaryInputs(status_register=StatusRegister(x=False, c=True), src=0, dst=0x0001),
    BinaryInputs(src=1, dst=0x0000),
    BinaryInputs(src=1, dst=0x0001)
])

ROR_LONG_REGISTER_INPUTS = LongInstructionInputs(inputs=[
    # Check that the operation looks like rotate right
    BinaryInputs(src=1, dst=0x8000_0000),
    BinaryInputs(src=1, dst=0x4000_0000),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4000_0000),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEAA_AA5A),
    BinaryInputs(src=4, dst=0xD3FF_A5AA),
    BinaryInputs(src=7, dst=0xA522_AAAA),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xE3CE_A55A),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA5E2_A55A),
    BinaryInputs(src=8763, dst=0xD4CC_B55A),
    BinaryInputs(src=2320, dst=0xA522_A55A),
    # Check the x flag behaviour (unchanged)
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0xD4CC_B55A),
    BinaryInputs(src=2, dst=0x4040_0000),
    BinaryInputs(src=2, dst=0x4040_0002),
    # Check the negative flag behaviour
    BinaryInputs(src=0, dst=0x0000_0001),
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x0000_0001),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0FE_CDCD),
    BinaryInputs(src=3, dst=0xC0FE_CDCD),
    BinaryInputs(src=3, dst=0x70FF_CDCD),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x0000_0000),
    BinaryInputs(src=32, dst=0x0000_00000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x8000_CDCD),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00_CDCD),
    # Check the carry flag behaviour (when shift is zero then carry is set to x)
    BinaryInputs(status_register=StatusRegister(x=True, c=False), src=0, dst=0x0000_0001),
    BinaryInputs(status_register=StatusRegister(x=False, c=True), src=0, dst=0x0000_0001),
    BinaryInputs(src=1, dst=0x0000_0000),
    BinaryInputs(src=1, dst=0x0000_0001)
])

# The shift for these operations is _always_ 1.
ROR_WORD_MEMORY_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like rotate right
    BinaryInputs(src=1, dst=0x8002),
    BinaryInputs(src=1, dst=0x4002),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4010),
    # Check the x flag behaviour (unchanged)
    BinaryInputs(src=1, dst=0x0000),
    BinaryInputs(src=1, dst=0x0001),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xCDCD),
    BinaryInputs(src=1, dst=0xCDCC),
    # Check the zero flag behaviour
    BinaryInputs(src=1, dst=0x0000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x7E00),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x0000),
    BinaryInputs(src=1, dst=0x0001)
])
