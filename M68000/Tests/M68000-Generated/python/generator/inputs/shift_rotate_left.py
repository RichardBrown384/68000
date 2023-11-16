"""
This module contains inputs for the shift rotate left instructions.
"""

from ..types.instruction_inputs import \
    BinaryInputs
from ..types.sized_instruction_inputs import \
    ByteInstructionInputs, WordInstructionInputs, LongInstructionInputs

from ..types.status_register import StatusRegister

ASL_BYTE_COUNT_INPUTS = ByteInstructionInputs(inputs=[
    # Check that the operation looks like arithmetic shift left
    BinaryInputs(src=1, dst=0x81),
    BinaryInputs(src=1, dst=0x41),
    BinaryInputs(src=1, dst=0xFFFF_FF88),
    # Different shift values
    BinaryInputs(src=3, dst=0xCE),
    BinaryInputs(src=4, dst=0xD3),
    BinaryInputs(src=7, dst=0xA5),
    # Check the x flag behaviour
    BinaryInputs(src=2, dst=0x40),
    BinaryInputs(src=2, dst=0x20),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0x10),
    BinaryInputs(src=3, dst=0x08),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x01),
    # Check the overflow flag behaviour (set if MSB changes)
    BinaryInputs(src=1, dst=0x80),  # should be set
    BinaryInputs(src=1, dst=0xC0),  # should be clear
    BinaryInputs(src=1, dst=0x40),  # should be set
    BinaryInputs(src=2, dst=0xC0),  # should be set
    BinaryInputs(src=2, dst=0xE0),  # should be clear
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(src=1, dst=0x40)
])

ASL_WORD_COUNT_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like arithmetic shift left
    BinaryInputs(src=1, dst=0x8001),
    BinaryInputs(src=1, dst=0x4001),
    BinaryInputs(src=1, dst=0xFFFF_4041),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD),
    BinaryInputs(src=4, dst=0xD3CC),
    BinaryInputs(src=7, dst=0xA522),
    # Check the x flag behaviour
    BinaryInputs(src=2, dst=0x4000),
    BinaryInputs(src=2, dst=0x2000),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0FF),
    BinaryInputs(src=3, dst=0x70FF),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0xFF00),
    # Check the overflow flag behaviour (set if MSB changes)
    BinaryInputs(src=1, dst=0x8000),  # should be set
    BinaryInputs(src=1, dst=0xC000),  # should be clear
    BinaryInputs(src=2, dst=0xC000),  # should be set
    BinaryInputs(src=2, dst=0xE000),  # should be clear
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4000)
])


ASL_LONG_COUNT_INPUTS = LongInstructionInputs(inputs=[
    # Check that the operation looks like arithmetic shift left
    BinaryInputs(src=1, dst=0x8000_1001),
    BinaryInputs(src=1, dst=0x4000_1001),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD_A55A),
    BinaryInputs(src=4, dst=0xD3CC_A55A),
    BinaryInputs(src=8, dst=0xA522_A55A),
    # Check the x flag behaviour
    BinaryInputs(src=2, dst=0x4040_0000),
    BinaryInputs(src=2, dst=0x2040_0002),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0FF_CDCD),
    BinaryInputs(src=3, dst=0x70FF_CDCD),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0xFF00_0000),
    # Check the overflow flag behaviour (set if MSB changes)
    BinaryInputs(src=1, dst=0x8000_FFFF),  # should be set
    BinaryInputs(src=1, dst=0xC000_FFFF),  # should be clear
    BinaryInputs(src=2, dst=0xC000_FFFF),  # should be set
    BinaryInputs(src=2, dst=0xE000_FFFF),  # should be clear
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x8000_0000),
    BinaryInputs(src=1, dst=0x4000_0000)
])

ASL_BYTE_REGISTER_INPUTS = ByteInstructionInputs(inputs=[
    # Check that the operation looks like arithmetic shift left
    BinaryInputs(src=1, dst=0x81),
    BinaryInputs(src=1, dst=0x41),
    BinaryInputs(src=3, dst=0xFFFF_FF4E),
    # Different shift values
    BinaryInputs(src=3, dst=0xCE),
    BinaryInputs(src=4, dst=0xD3),
    BinaryInputs(src=7, dst=0xA5),
    BinaryInputs(src=900, dst=0xD3),
    BinaryInputs(src=803, dst=0xA5),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x81),
    BinaryInputs(src=2, dst=0x80),
    BinaryInputs(src=2, dst=0x40),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0),
    BinaryInputs(src=3, dst=0x70),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0xFF),
    # Check the overflow flag behaviour (set if MSB changes)
    BinaryInputs(src=1, dst=0x80),  # should be set
    BinaryInputs(src=1, dst=0xC0),  # should be clear
    BinaryInputs(src=2, dst=0xC0),  # should be set
    BinaryInputs(src=2, dst=0xE0),  # should be clear
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=True), src=0, dst=0xEE),
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(src=1, dst=0x40),
    BinaryInputs(src=2, dst=0xC0)
])

ASL_WORD_REGISTER_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like arithmetic shift left
    BinaryInputs(src=1, dst=0x8001),
    BinaryInputs(src=1, dst=0x4001),
    BinaryInputs(src=3, dst=0xFFFF_4EFF),
    # Different shift values
    BinaryInputs(src=3, dst=0xCECD),
    BinaryInputs(src=4, dst=0xD3CD),
    BinaryInputs(src=7, dst=0xA5CD),
    BinaryInputs(src=900, dst=0xD3CD),
    BinaryInputs(src=803, dst=0xA5CD),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x8001),
    BinaryInputs(src=2, dst=0x0F00),
    BinaryInputs(src=2, dst=0x7F02),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0CD),
    BinaryInputs(src=3, dst=0x70CD),
    # Check the zero flag behaviour
    BinaryInputs(src=16, dst=0xFFFF),
    # Check the overflow flag behaviour (set if MSB changes)
    BinaryInputs(src=1, dst=0x8000),  # should be set
    BinaryInputs(src=1, dst=0xC000),  # should be clear
    BinaryInputs(src=2, dst=0xC000),  # should be set
    BinaryInputs(src=2, dst=0xE000),  # should be clear
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=True), src=0, dst=0x11EE),
    BinaryInputs(src=1, dst=0x7FFF_0000),
    BinaryInputs(src=1, dst=0x8FFF_0001),
    BinaryInputs(src=2, dst=0xCFFF_0002)
])

ASL_LONG_REGISTER_INPUTS = LongInstructionInputs(inputs=[
    # Check that the operation looks like arithmetic shift left
    BinaryInputs(src=1, dst=0x8000_0010),
    BinaryInputs(src=1, dst=0x4000_0010),
    BinaryInputs(src=3, dst=0xFFFF_4EFF),
    # Different shift values
    BinaryInputs(src=3, dst=0xCECD_BCBC),
    BinaryInputs(src=4, dst=0xD3CD_BCBC),
    BinaryInputs(src=7, dst=0xA5CD_BCBC),
    BinaryInputs(src=457, dst=0xD3CD_BCBC),
    BinaryInputs(src=1666, dst=0xA5CD_BCBC),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x8000_0001),
    BinaryInputs(src=2, dst=0x0F00_0000),
    BinaryInputs(src=2, dst=0xCF00_0002),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0CD_FECD),
    BinaryInputs(src=3, dst=0x70CD_FECD),
    # Check the zero flag behaviour
    BinaryInputs(src=32, dst=0xFFFF_FFFF),
    # Check the overflow flag behaviour (set if MSB changes)
    BinaryInputs(src=1, dst=0x8000_0000),  # should be set
    BinaryInputs(src=1, dst=0xC000_0000),  # should be clear
    BinaryInputs(src=2, dst=0xC000_0000),  # should be set
    BinaryInputs(src=2, dst=0xE000_0000),  # should be clear
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=True), src=0, dst=0xFFCC_CCEE),
    BinaryInputs(src=1, dst=0x8FFF_0000),
    BinaryInputs(src=1, dst=0x7FFF_0001),
    BinaryInputs(src=2, dst=0xCFFF_0002)
])

# The shift for these operations is _always_ 1.
ASL_WORD_MEMORY_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like arithmetic shift left
    BinaryInputs(src=1, dst=0x8001),
    BinaryInputs(src=1, dst=0x4001),
    # Check the x flag behaviour
    BinaryInputs(src=1, dst=0x7F00),
    BinaryInputs(src=1, dst=0x7F01),
    # Check the negative flag behaviour
    BinaryInputs(src=1, dst=0x80CD),
    BinaryInputs(src=1, dst=0x70CD),
    # Check the zero flag behaviour
    BinaryInputs(src=1, dst=0x8000),
    # Check the overflow flag behaviour (set if MSB changes)
    BinaryInputs(src=1, dst=0x8000),  # should be set
    BinaryInputs(src=1, dst=0xC000),  # should be clear
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x8A00),
    BinaryInputs(src=1, dst=0x4A01),
])

LSL_BYTE_COUNT_INPUTS = ByteInstructionInputs(inputs=[
    # Check that the operation looks like logical shift left
    BinaryInputs(src=1, dst=0x81),
    BinaryInputs(src=1, dst=0x41),
    BinaryInputs(src=1, dst=0xFFFF_FF18),
    # Different shift values
    BinaryInputs(src=3, dst=0xEC),
    BinaryInputs(src=4, dst=0x7F),
    BinaryInputs(src=7, dst=0xC9),
    # Check the x flag behaviour
    BinaryInputs(src=2, dst=0x80),
    BinaryInputs(src=3, dst=0x40),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0),
    BinaryInputs(src=3, dst=0x70),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0xFF),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x80),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC0),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0xFF),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(src=1, dst=0x40)
])

LSL_WORD_COUNT_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like logical shift left
    BinaryInputs(src=1, dst=0x8010),
    BinaryInputs(src=1, dst=0x4010),
    BinaryInputs(src=1, dst=0xFFFF_4140),
    # Different shift values
    BinaryInputs(src=3, dst=0xCE99),
    BinaryInputs(src=4, dst=0xD56C),
    BinaryInputs(src=3, dst=0xA322),
    # Check the x flag behaviour
    BinaryInputs(src=2, dst=0x8000),
    BinaryInputs(src=2, dst=0x4000),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0FF),
    BinaryInputs(src=3, dst=0x70FF),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0xFF00),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC000),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4000)
])

LSL_LONG_COUNT_INPUTS = LongInstructionInputs(inputs=[
    # Check that the operation looks like logical shift left
    BinaryInputs(src=1, dst=0x8000_1000),
    BinaryInputs(src=1, dst=0x4000_1000),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEEE_5AA5),
    BinaryInputs(src=4, dst=0xD3DD_5AA5),
    BinaryInputs(src=7, dst=0xA5FF_5AA5),
    # Check the x flag behaviour
    BinaryInputs(src=2, dst=0x4040_0000),
    BinaryInputs(src=2, dst=0x8040_0002),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0FF_DCDC),
    BinaryInputs(src=3, dst=0x70FF_DCDC),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0xFF00_0000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000_CDCD),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC000_CDCD),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x7E00_CDCD),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x8000_0000),
    BinaryInputs(src=1, dst=0x4000_0001)
])

LSL_BYTE_REGISTER_INPUTS = ByteInstructionInputs(inputs=[
    # Check that the operation looks like logical shift left
    BinaryInputs(src=1, dst=0x81),
    BinaryInputs(src=1, dst=0x41),
    BinaryInputs(src=3, dst=0xFFFF_FF4E),
    # Different shift values
    BinaryInputs(src=3, dst=0xCE),
    BinaryInputs(src=4, dst=0xD3),
    BinaryInputs(src=7, dst=0xA5),
    BinaryInputs(src=901, dst=0xD3),
    BinaryInputs(src=802, dst=0xA5),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x81),
    BinaryInputs(src=2, dst=0x80),
    BinaryInputs(src=2, dst=0x40),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0),
    BinaryInputs(src=3, dst=0x70),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0xFF),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x80),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC0),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E),
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=True), src=0, dst=0xEE),
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(src=1, dst=0x40),
    BinaryInputs(src=2, dst=0xC0)
])

LSL_WORD_REGISTER_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like logical shift left
    BinaryInputs(src=1, dst=0x8040),
    BinaryInputs(src=1, dst=0x4040),
    BinaryInputs(src=3, dst=0xFFFF_4EFF),
    # Different shift values
    BinaryInputs(src=3, dst=0xCAAD),
    BinaryInputs(src=4, dst=0xDC3D),
    BinaryInputs(src=7, dst=0xAC5D),
    BinaryInputs(src=900, dst=0xDC3D),
    BinaryInputs(src=803, dst=0xAC5D),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x8001),
    BinaryInputs(src=2, dst=0x8F00),
    BinaryInputs(src=2, dst=0xCF02),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0CD),
    BinaryInputs(src=3, dst=0x70CD),
    # Check the zero flag behaviour
    BinaryInputs(src=16, dst=0xFFFF),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC000),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00),
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=True), src=0, dst=0xCCEE),
    BinaryInputs(src=1, dst=0x8F00_FF00),
    BinaryInputs(src=1, dst=0x7F00_FF01),
    BinaryInputs(src=2, dst=0xCF00_FF02)
])

LSL_LONG_REGISTER_INPUTS = LongInstructionInputs(inputs=[
    # Check that the operation looks like logical shift left
    BinaryInputs(src=1, dst=0x8000_1000),
    BinaryInputs(src=1, dst=0x4000_1000),
    BinaryInputs(src=3, dst=0xFFFF_4EFF),
    # Different shift values
    BinaryInputs(src=3, dst=0xCECD_BCBC),
    BinaryInputs(src=4, dst=0xD3CD_BCBC),
    BinaryInputs(src=7, dst=0xA5CD_BCBC),
    BinaryInputs(src=798, dst=0xD3CD_BCBC),
    BinaryInputs(src=6661, dst=0xA5CD_BCBC),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x8000_0001),
    BinaryInputs(src=2, dst=0x8F00_0000),
    BinaryInputs(src=2, dst=0x7F00_0002),
    # Check the negative flag behaviour
    BinaryInputs(src=3, dst=0xC0CD_FECD),
    BinaryInputs(src=3, dst=0x70CD_FECD),
    # Check the zero flag behaviour
    BinaryInputs(src=32, dst=0xFFFF_FFFF),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000_0000),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC000_0000),
    BinaryInputs(status_register=StatusRegister(v=True), src=17, dst=0x7E00_0000),
    # Check the carry flag behaviour
    BinaryInputs(status_register=StatusRegister(c=True), src=0, dst=0xCCDD_AAEE),
    BinaryInputs(src=1, dst=0x7FFF_0000),
    BinaryInputs(src=1, dst=0x8FFF_0001),
    BinaryInputs(src=2, dst=0xCFFF_0002)
])

# The shift for these operations is _always_ 1.
LSL_WORD_MEMORY_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like logical shift left
    BinaryInputs(src=1, dst=0x8001),
    BinaryInputs(src=1, dst=0x4001),
    # Check the x flag behaviour
    BinaryInputs(src=1, dst=0x7F00),
    BinaryInputs(src=1, dst=0x8F01),
    # Check the negative flag behaviour
    BinaryInputs(src=1, dst=0x80CD),
    BinaryInputs(src=1, dst=0x70CD),
    # Check the zero flag behaviour
    BinaryInputs(src=1, dst=0x8000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC000),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x7E00),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x8A00),
    BinaryInputs(src=1, dst=0x4A01),
])

ROXL_BYTE_COUNT_INPUTS = ByteInstructionInputs(inputs=[
    # Check that the operation looks like rotate extended left
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x48),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xFFFF_FF78),
    # Different shift values
    BinaryInputs(src=3, dst=0xCE),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD3),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA5),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x80),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0xC0),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=8, dst=0xFF),
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(src=1, dst=0x70),
    # Check the zero flag behaviour
    BinaryInputs(src=1, dst=0x00),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x80),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC0),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(src=1, dst=0x41)
])

ROXL_WORD_COUNT_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like rotate extended left
    BinaryInputs(src=1, dst=0x8010),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4010),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xFFFF_4040),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD3CC),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA522),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x4002),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=8, dst=0xFF80),
    BinaryInputs(src=3, dst=0xC0FF),
    BinaryInputs(src=3, dst=0x70FF),
    # Check the zero flag behaviour
    BinaryInputs(src=1, dst=0x8000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC000),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4001)
])

ROXL_LONG_COUNT_INPUTS = LongInstructionInputs(inputs=[
    # Check that the operation looks like rotate extended left
    BinaryInputs(src=1, dst=0x800A_00A0),
    BinaryInputs(src=1, dst=0x400A_00A0),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x400A_A000),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD_A55A),
    BinaryInputs(src=4, dst=0xD3CC_A55A),
    BinaryInputs(src=7, dst=0xA522_A55A),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD3CC_A55A),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA522_A55A),
    # Check the x flag behaviour
    BinaryInputs(src=2, dst=0x8040_0000),
    BinaryInputs(src=2, dst=0x4040_0002),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x40FF_CDCD),
    BinaryInputs(src=3, dst=0xC0FF_CDCD),
    BinaryInputs(src=3, dst=0x70FF_CDCD),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0xFF00_0000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000_CDCD),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC000_CDCD),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00_CDCD),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x8000_0000),
    BinaryInputs(src=1, dst=0x4000_0001)
])

ROXL_BYTE_REGISTER_INPUTS = ByteInstructionInputs(inputs=[
    # Check that the operation looks like rotate extended left
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x41),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xFFFF_FF18),
    # Different shift values
    BinaryInputs(src=3, dst=0xCE),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD3),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA5),
    BinaryInputs(src=803, dst=0xD3),
    BinaryInputs(src=696, dst=0xA5),
    # Check the x flag behaviour
    BinaryInputs(src=0, dst=0x01),
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x01),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x80),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x42),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0),
    BinaryInputs(src=0, dst=0xC0),
    BinaryInputs(src=1, dst=0xC0),
    BinaryInputs(src=1, dst=0x80),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0xFF),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x80),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC0),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E),
    # Check the carry flag behaviour (when shift is zero then carry is set to x)
    BinaryInputs(status_register=StatusRegister(x=True, c=False), src=0, dst=0x01),
    BinaryInputs(status_register=StatusRegister(x=False, c=True), src=0, dst=0x01),
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(src=1, dst=0x41)
])

ROXL_WORD_REGISTER_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like rotate extended left
    BinaryInputs(src=1, dst=0x8001),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4010),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xFFFF_4140),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD3CC),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA522),
    BinaryInputs(src=777, dst=0xD3CC),
    BinaryInputs(src=779, dst=0xA522),
    # Check the x flag behaviour
    BinaryInputs(src=0, dst=0x0001),
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x0001),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x4002),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0FF),
    BinaryInputs(src=0, dst=0xC0FF),
    BinaryInputs(src=3, dst=0xC0FF),
    BinaryInputs(src=3, dst=0x70FF),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x0000),
    BinaryInputs(src=16, dst=0x0000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC000),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00),
    # Check the carry flag behaviour (when shift is zero then carry is set to x)
    BinaryInputs(status_register=StatusRegister(x=True, c=False), src=0, dst=0x0001),
    BinaryInputs(status_register=StatusRegister(x=False, c=True), src=0, dst=0x0001),
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4001)
])

ROXL_LONG_REGISTER_INPUTS = LongInstructionInputs(inputs=[
    # Check that the operation looks like rotate extended left
    BinaryInputs(src=1, dst=0x8000_1000),
    BinaryInputs(src=1, dst=0x4000_1000),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4000_1000),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD_A55A),
    BinaryInputs(src=4, dst=0xD3CC_A55A),
    BinaryInputs(src=7, dst=0xA522_A55A),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD3CC_A55A),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA522_A55A),
    BinaryInputs(src=8763, dst=0xD3CC_A55A),
    BinaryInputs(src=2320, dst=0xA522_A55A),
    # Check the x flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0xD3CC_A55A),
    BinaryInputs(src=2, dst=0x8040_0000),
    BinaryInputs(src=2, dst=0x4040_0002),
    # Check the negative flag behaviour
    BinaryInputs(src=0, dst=0x4000_0001),
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x4000_0001),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0FF_CDCD),
    BinaryInputs(src=3, dst=0xC0FF_CDCD),
    BinaryInputs(src=3, dst=0x70FF_CDCD),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x0000_0000),
    BinaryInputs(src=32, dst=0x0000_00000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000_CDCD),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC000_CDCD),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00_CDCD),
    # Check the carry flag behaviour (when shift is zero then carry is set to x)
    BinaryInputs(status_register=StatusRegister(x=True, c=False), src=0, dst=0x0000_0001),
    BinaryInputs(status_register=StatusRegister(x=False, c=True), src=0, dst=0x0000_0001),
    BinaryInputs(src=1, dst=0x8000_0000),
    BinaryInputs(src=1, dst=0x4000_0001)
])

# The shift for these operations is _always_ 1.
ROXL_WORD_MEMORY_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like rotate extended left
    BinaryInputs(src=1, dst=0x8010),
    BinaryInputs(src=1, dst=0x4010),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4010),
    # Check the x flag behaviour
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4001),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xCDCD),
    BinaryInputs(src=1, dst=0xCDCD),
    BinaryInputs(src=1, dst=0x8DCD),
    # Check the zero flag behaviour
    BinaryInputs(src=1, dst=0x0000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC000),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x7E00),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4001)
])

ROL_BYTE_COUNT_INPUTS = ByteInstructionInputs(inputs=[
    # Check that the operation looks like rotate left
    BinaryInputs(src=1, dst=0x83),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x42),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xFFFF_FF18),
    # Different shift values
    BinaryInputs(src=3, dst=0xCE),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD3),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA5),
    # Check the x flag behaviour (unchanged)
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x80),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x40),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC1),
    BinaryInputs(src=1, dst=0x81),
    BinaryInputs(src=1, dst=0x40),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x00),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x80),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC0),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(src=1, dst=0x41)
])

ROL_WORD_COUNT_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like rotate left
    BinaryInputs(src=1, dst=0x8102),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4030),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xFFFF_4340),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD3CC),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA522),
    # Check the x flag behaviour (unchanged)
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x4002),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0FF),
    BinaryInputs(src=3, dst=0xC0FF),
    BinaryInputs(src=3, dst=0x70F0),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x0000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC000),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4001)
])

ROL_LONG_COUNT_INPUTS = LongInstructionInputs(inputs=[
    # Check that the operation looks like rotate left
    BinaryInputs(src=1, dst=0x8000_1002),
    BinaryInputs(src=1, dst=0x4000_1002),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4000_1002),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD_A55A),
    BinaryInputs(src=4, dst=0xD3CC_A55A),
    BinaryInputs(src=7, dst=0xA522_A55A),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD3CC_A55A),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA522_A55A),
    # Check the x flag behaviour (unchanged)
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x8040_0000),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x4040_0002),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0FF_CDCD),
    BinaryInputs(src=3, dst=0xC0FF_CDCD),
    BinaryInputs(src=3, dst=0x70FF_CDCD),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x0000_0000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000_CDCD),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC000_CDCD),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00_CDCD),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x8000_0000),
    BinaryInputs(src=1, dst=0x4000_0001)
])

ROL_BYTE_REGISTER_INPUTS = ByteInstructionInputs(inputs=[
    # Check that the operation looks like rotate left
    BinaryInputs(src=1, dst=0x81),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x401),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xFFFF_FF18),
    # Different shift values
    BinaryInputs(src=3, dst=0xCE),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD3),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA5),
    BinaryInputs(src=803, dst=0xD3),
    BinaryInputs(src=696, dst=0xA5),
    # Check the x flag behaviour (unchanged)
    BinaryInputs(src=0, dst=0x01),
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x01),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x80),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x40),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0),
    BinaryInputs(src=0, dst=0xC0),
    BinaryInputs(src=1, dst=0xC0),
    BinaryInputs(src=1, dst=0x80),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x00),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x80),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC0),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E),
    # Check the carry flag behaviour (when shift is zero then carry is set to x)
    BinaryInputs(status_register=StatusRegister(x=True, c=False), src=0, dst=0x01),
    BinaryInputs(status_register=StatusRegister(x=False, c=True), src=0, dst=0x01),
    BinaryInputs(src=1, dst=0x80),
    BinaryInputs(src=1, dst=0x41)
])

ROL_WORD_REGISTER_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like rotate left
    BinaryInputs(src=1, dst=0x8010),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4010),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xFFFF_4040),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD3CC),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA522),
    BinaryInputs(src=777, dst=0xD3CC),
    BinaryInputs(src=779, dst=0xA522),
    # Check the x flag behaviour (unchanged)
    BinaryInputs(src=0, dst=0x0001),
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x0001),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(x=True), src=2, dst=0x4002),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xC0FF),
    BinaryInputs(src=0, dst=0xC0FF),
    BinaryInputs(src=3, dst=0xC0FF),
    BinaryInputs(src=3, dst=0x70F0),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x0000),
    BinaryInputs(src=16, dst=0x0000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC000),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00),
    # Check the carry flag behaviour (when shift is zero then carry is set to x)
    BinaryInputs(status_register=StatusRegister(x=True, c=False), src=0, dst=0x0001),
    BinaryInputs(status_register=StatusRegister(x=False, c=True), src=0, dst=0x0001),
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4001)
])

ROL_LONG_REGISTER_INPUTS = LongInstructionInputs(inputs=[
    # Check that the operation looks like rotate left
    BinaryInputs(src=1, dst=0x8000_1000),
    BinaryInputs(src=1, dst=0x4000_1000),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4000_1000),
    # Different shift values
    BinaryInputs(src=3, dst=0xCEDD_A55A),
    BinaryInputs(src=4, dst=0xD3CC_A55A),
    BinaryInputs(src=7, dst=0xA522_A55A),
    BinaryInputs(status_register=StatusRegister(x=True), src=4, dst=0xD3CC_A55A),
    BinaryInputs(status_register=StatusRegister(x=True), src=7, dst=0xA522_A55A),
    BinaryInputs(src=8763, dst=0xD3CC_A55A),
    BinaryInputs(src=2320, dst=0xA522_A55A),
    # Check the x flag behaviour (unchanged)
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0xD3CC_A55A),
    BinaryInputs(src=2, dst=0x4040_0000),
    BinaryInputs(src=2, dst=0x8040_0002),
    # Check the negative flag behaviour
    BinaryInputs(src=0, dst=0x0000_0001),
    BinaryInputs(status_register=StatusRegister(x=True), src=0, dst=0x0000_0001),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x40FF_CDCD),
    BinaryInputs(src=3, dst=0xC0FF_CDCD),
    BinaryInputs(src=3, dst=0x70FF_CDCD),
    # Check the zero flag behaviour
    BinaryInputs(src=8, dst=0x0000_0000),
    BinaryInputs(src=32, dst=0x0000_00000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000_CDCD),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC000_CDCD),
    BinaryInputs(status_register=StatusRegister(v=True), src=8, dst=0x7E00_CDCD),
    # Check the carry flag behaviour (when shift is zero then carry is set to x)
    BinaryInputs(status_register=StatusRegister(x=True, c=False), src=0, dst=0x0000_0001),
    BinaryInputs(status_register=StatusRegister(x=False, c=True), src=0, dst=0x0000_0001),
    BinaryInputs(src=1, dst=0x8000_0000),
    BinaryInputs(src=1, dst=0x4000_0001)
])

# The shift for these operations is _always_ 1.
ROL_WORD_MEMORY_INPUTS = WordInstructionInputs(inputs=[
    # Check that the operation looks like rotate left
    BinaryInputs(src=1, dst=0x8002),
    BinaryInputs(src=1, dst=0x4002),
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0x4010),
    # Check the x flag behaviour (unchanged)
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4001),
    # Check the negative flag behaviour
    BinaryInputs(status_register=StatusRegister(x=True), src=1, dst=0xCDCD),
    BinaryInputs(src=1, dst=0x8DCC),
    # Check the zero flag behaviour
    BinaryInputs(src=1, dst=0x0000),
    # Check the overflow flag behaviour (always reset)
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0x8000),
    BinaryInputs(status_register=StatusRegister(v=True), src=1, dst=0xC000),
    # Check the carry flag behaviour
    BinaryInputs(src=1, dst=0x8000),
    BinaryInputs(src=1, dst=0x4001)
])
