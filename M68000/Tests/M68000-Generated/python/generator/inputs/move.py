from ..types.instruction_inputs import BinaryInputs
from ..types.sized_instruction_inputs import \
    ByteInstructionInputs, \
    WordInstructionInputs, \
    LongInstructionInputs
from ..types.status_register import StatusRegister

MOVE_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    BinaryInputs(src=0xEF, dst=0x35),  # check operation is something like move
    BinaryInputs(src=0x00FF_00FF, dst=0xA5A5_A52D),  # check byte operation on register
    # check x flag doesn't influence result
    BinaryInputs(status_register=StatusRegister(x=True), src=0xFF, dst=0xCE),
    BinaryInputs(src=0x80, dst=0xEE),  # check negative flag
    BinaryInputs(src=0x00, dst=0x00),  # check trivial zero flag
    BinaryInputs(src=0x00, dst=0x01),  # check non-trivial zero flag
    # check overflow flag is cleared
    BinaryInputs(status_register=StatusRegister(v=True), src=0x7F, dst=0x01),
    # check carry flag is cleared
    BinaryInputs(status_register=StatusRegister(c=True), src=0x7F, dst=0x71),
])

MOVE_WORD_INPUTS = WordInstructionInputs(inputs=[
    BinaryInputs(src=0xEFDD, dst=0x1235),  # check operation is something like move
    BinaryInputs(src=0xCCFF_EEFF, dst=0xA55A_A52D),  # check word operation on register
    # check x flag doesn't influence result
    BinaryInputs(status_register=StatusRegister(x=True), src=0xFFFF, dst=0xCDCE),
    BinaryInputs(src=0x8000, dst=0x7DEE),  # check negative flag
    BinaryInputs(src=0x0000, dst=0x0000),  # check trivial zero flag
    BinaryInputs(src=0x0000, dst=0x0001),  # check non-trivial zero flag
    # check overflow flag is cleared
    BinaryInputs(status_register=StatusRegister(v=True), src=0x7F12, dst=0x0101),
    # check carry flag is cleared
    BinaryInputs(status_register=StatusRegister(c=True), src=0x7F21, dst=0x1771),
])

MOVE_LONG_INPUTS = LongInstructionInputs(inputs=[
    BinaryInputs(src=0xEFDD_CCAA, dst=0x9876_1235),  # check operation is something like move
    BinaryInputs(src=0xCCFF_EEFF, dst=0xA55A_A52D),  # check long operation on register
    # check x flag doesn't influence result
    BinaryInputs(status_register=StatusRegister(x=True), src=0xFFFF_FFFF, dst=0xBCDA_CDCE),
    BinaryInputs(src=0x8000_0000, dst=0x7654_7DEE),  # check negative flag
    BinaryInputs(src=0x0000_0000, dst=0x0000_0000),  # check trivial zero flag
    BinaryInputs(src=0x0000_0000, dst=0x0001_0001),  # check non-trivial zero flag
    # check overflow flag is cleared
    BinaryInputs(status_register=StatusRegister(v=True), src=0x5432_7F12, dst=0x0101_0101),
    # check carry flag is cleared
    BinaryInputs(status_register=StatusRegister(c=True), src=0x5432_7F21, dst=0x1771_1771),
])
