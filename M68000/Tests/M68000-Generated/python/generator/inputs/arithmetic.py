"""
This module contains inputs for the standard arithmetic instructions.
"""

from ..types.instruction_inputs import \
    BinaryInputs
from ..types.sized_instruction_inputs import \
    ByteInstructionInputs, \
    WordInstructionInputs, \
    LongInstructionInputs

from ..types.status_register import StatusRegister

ADD_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    BinaryInputs(src=0x08, dst=0x09),  # check operation is something like addition
    BinaryInputs(src=0x5A5A5AFF, dst=0xA5A5A5FE),  # check byte operation on register
    # check x flag doesn't influence result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x08, dst=0x09),
    BinaryInputs(src=0x80, dst=0x04),  # check negative flag
    BinaryInputs(src=0x00, dst=0x00),  # check trivial zero flag
    BinaryInputs(src=0xFF, dst=0x01),  # check zero flag
    BinaryInputs(src=0x7F, dst=0x01),  # check overflow from two positives
    BinaryInputs(src=0x80, dst=0x81),  # check overflow from two negatives
    BinaryInputs(src=0xFA, dst=0x20),  # check carry flag
])

ADD_WORD_INPUTS = WordInstructionInputs(inputs=[
    BinaryInputs(src=0x132E, dst=0x3AF3),  # check operation is something like addition
    BinaryInputs(src=0xA1A2132E, dst=0x1234FAF3),  # check word operation on register
    # check x flag doesn't influence result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x8080, dst=0x0303),
    BinaryInputs(src=0x8000, dst=0x0002),  # check negative flag
    BinaryInputs(src=0x0000, dst=0x0000),  # check trivial zero flag
    BinaryInputs(src=0xFFFE, dst=0x0002),  # check zero flag
    BinaryInputs(src=0x7FFF, dst=0x0001),  # check overflow from two positives
    BinaryInputs(src=0x8000, dst=0x8001),  # check overflow from two negatives
    BinaryInputs(src=0xFA11, dst=0x2000),  # check carry flag
])

ADD_LONG_INPUTS = LongInstructionInputs(inputs=[
    # check operation is something like addition
    BinaryInputs(src=0x71A2_F32E, dst=0x123C_FAF3),
    # check x flag doesn't influence result
    BinaryInputs(
        status_register=StatusRegister(x=True),
        src=0x0808_8080,
        dst=0x3030_0303
    ),
    BinaryInputs(src=0x8000_0000, dst=0x0000_0002),  # check negative flag
    BinaryInputs(src=0x0000_0000, dst=0x0000_0000),  # check trivial zero flag
    BinaryInputs(src=0xFFFF_FFFD, dst=0x0000_0003),  # check zero flag
    # check overflow from two positives
    BinaryInputs(src=0x7FFF_FFFF, dst=0x0000_0001),
    # check overflow from two negatives
    BinaryInputs(src=0x8000_0000, dst=0x8000_0001),
    BinaryInputs(src=0xFA11_1111, dst=0x2000_0000),  # check carry flag
])

SUB_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    BinaryInputs(src=0x33, dst=0x11),  # check operation is something like subtraction
    BinaryInputs(src=0x5A5A5A01, dst=0xA5A5A5FE),  # check byte operation on register
    # check x flag doesn't influence result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x33, dst=0x11),
    BinaryInputs(src=0xC0, dst=0x04),  # check negative flag
    BinaryInputs(src=0x00, dst=0x00),  # check trivial zero flag
    BinaryInputs(src=0x55, dst=0x55),  # check zero flag
    BinaryInputs(src=0xFF, dst=0x7F),  # check overflow from positive minuend
    BinaryInputs(src=0x01, dst=0x80),  # check overflow from negative minuend
    BinaryInputs(src=0xF0, dst=0x10),  # check carry flag
])

SUB_WORD_INPUTS = WordInstructionInputs(inputs=[
    # check operation is something like subtraction
    BinaryInputs(src=0x2233, dst=0x5111),
    BinaryInputs(src=0x5A5A5A01, dst=0xA5A5A5FE),  # check word operation on register
    # check x flag doesn't influence result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x2233, dst=0x5111),
    BinaryInputs(src=0xC000, dst=0x0004),  # check negative flag
    BinaryInputs(src=0x0000, dst=0x0000),  # check trivial zero flag
    BinaryInputs(src=0xA5A5, dst=0xA5A5),  # check zero flag
    BinaryInputs(src=0xFF00, dst=0x7F00),  # check overflow from positive minuend
    BinaryInputs(src=0x0001, dst=0x8000),  # check overflow from negative minuend
    BinaryInputs(src=0xF000, dst=0x1000),  # check carry flag
])

SUB_LONG_INPUTS = LongInstructionInputs(inputs=[
    # check operation is something like subtraction
    BinaryInputs(src=0x5A5A_5A01, dst=0xA5A5_A5FE),
    # check x flag doesn't influence result
    BinaryInputs(
        status_register=StatusRegister(x=True),
        src=0x7766_2233,
        dst=0x9988_5111
    ),
    BinaryInputs(src=0xC000_0000, dst=0x0004_0000),  # check negative flag
    BinaryInputs(src=0x0000_0000, dst=0x0000_0000),  # check trivial zero flag
    BinaryInputs(src=0xA5A5_0000, dst=0xA5A5_0000),  # check zero flag
    # check overflow from positive minuend
    BinaryInputs(src=0xFF00_0000, dst=0x7F00_0000),
    # check overflow from negative minuend
    BinaryInputs(src=0x0001_0000, dst=0x8000_0000),
    BinaryInputs(src=0xF000_0000, dst=0x1000_0000),  # check carry flag
])

CMP_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    BinaryInputs(src=0x33, dst=0x11),  # check operation is something like subtraction
    BinaryInputs(src=0x5A5A5A01, dst=0xA5A5A5FE),  # check byte operation on register
    # check x flag doesn't influence result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x11, dst=0x33),
    # check x isn't influenced by result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x33, dst=0x11),
    BinaryInputs(src=0xC0, dst=0x04),  # check negative flag
    BinaryInputs(src=0x00, dst=0x00),  # check trivial zero flag
    BinaryInputs(src=0x55, dst=0x55),  # check zero flag
    BinaryInputs(src=0xFF, dst=0x7F),  # check overflow from positive minuend
    BinaryInputs(src=0x01, dst=0x80),  # check overflow from negative minuend
    BinaryInputs(src=0xF0, dst=0x10),  # check carry flag
])

CMP_WORD_INPUTS = WordInstructionInputs(inputs=[
    # check operation is something like subtraction
    BinaryInputs(src=0x2233, dst=0x5111),
    BinaryInputs(src=0x5A5A5A01, dst=0xA5A5A5FE),  # check word operation on register
    # check x flag doesn't influence result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x2233, dst=0x5111),
    # check x isn't influenced by result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x5111, dst=0x2233),
    BinaryInputs(src=0xC000, dst=0x0004),  # check negative flag
    BinaryInputs(src=0x0000, dst=0x0000),  # check trivial zero flag
    BinaryInputs(src=0xA5A5, dst=0xA5A5),  # check zero flag
    BinaryInputs(src=0xFF00, dst=0x7F00),  # check overflow from positive minuend
    BinaryInputs(src=0x0001, dst=0x8000),  # check overflow from negative minuend
    BinaryInputs(src=0xF000, dst=0x1000),  # check carry flag
])

CMP_LONG_INPUTS = LongInstructionInputs(inputs=[
    # check operation is something like subtraction
    BinaryInputs(src=0x7766_2233, dst=0x9988_5111),
    # check x flag doesn't influence result
    BinaryInputs(
        status_register=StatusRegister(x=True),
        src=0x7766_2233,
        dst=0x9988_5111
    ),
    # check x isn't influenced by result
    BinaryInputs(
        status_register=StatusRegister(x=True),
        src=0x9988_5111,
        dst=0x7766_2233
    ),
    BinaryInputs(src=0xC000_0000, dst=0x0004_0000),  # check negative flag
    BinaryInputs(src=0x0000_0000, dst=0x0000_0000),  # check trivial zero flag
    BinaryInputs(src=0xA5A5_0000, dst=0xA5A5_0000),  # check zero flag
    # check overflow from positive minuend
    BinaryInputs(src=0xFF00_0000, dst=0x7F00_0000),
    # check overflow from negative minuend
    BinaryInputs(src=0x0001_0000, dst=0x8000_0000),
    BinaryInputs(src=0xF000_0000, dst=0x1000_0000),  # check carry flag,
])

AND_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    BinaryInputs(src=0xFE, dst=0x35),  # check operation is something like logical and
    BinaryInputs(src=0x00FF_00FF, dst=0xA5A5A52D),  # check byte operation on register
    # check x flag doesn't influence result
    BinaryInputs(status_register=StatusRegister(x=True), src=0xFF, dst=0xCD),
    BinaryInputs(src=0x80, dst=0xFF),  # check negative flag
    BinaryInputs(src=0x00, dst=0x00),  # check trivial zero flag
    BinaryInputs(src=0xAA, dst=0x55),  # check zero flag
    # check overflow flag is cleared
    BinaryInputs(status_register=StatusRegister(v=True), src=0x7F, dst=0x01),
    # check carry flag is cleared
    BinaryInputs(status_register=StatusRegister(c=True), src=0x7F, dst=0x71),
])

AND_WORD_INPUTS = WordInstructionInputs(inputs=[
    # check operation is something like logical and
    BinaryInputs(src=0xFEFE, dst=0xFF35),
    BinaryInputs(src=0x0000_EEEE, dst=0xA5A5A52D),  # check word operation on register
    # check x flag doesn't influence result
    BinaryInputs(status_register=StatusRegister(x=True), src=0xFEFE, dst=0xFF35),
    BinaryInputs(src=0x8000, dst=0xFFFF),  # check negative flag
    BinaryInputs(src=0x0000, dst=0x0000),  # check trivial zero flag
    BinaryInputs(src=0xAA55, dst=0x55AA),  # check zero flag
    # check overflow flag is cleared
    BinaryInputs(status_register=StatusRegister(v=True), src=0x7FFF, dst=0x0101),
    # check carry flag is cleared
    BinaryInputs(status_register=StatusRegister(c=True), src=0x7FFF, dst=0x7181),
])

AND_LONG_INPUTS = LongInstructionInputs(inputs=[
    # check operation is something like logical and
    BinaryInputs(src=0xAA55_FEFE, dst=0xFFFF_FF35),
    # check x flag doesn't influence result
    BinaryInputs(
        status_register=StatusRegister(x=True),
        src=0xAA55_FEFE,
        dst=0xFFFF_FF35
    ),
    BinaryInputs(src=0x8000_0000, dst=0xFFFF_FFFF),  # check negative flag
    BinaryInputs(src=0x0000_0000, dst=0x0000_0000),  # check trivial zero flag
    BinaryInputs(src=0xAA55_55AA, dst=0x55AA_55AA),  # check zero flag
    # check overflow flag is cleared
    BinaryInputs(
        status_register=StatusRegister(v=True),
        src=0x7FFF_FFFF,
        dst=0x0101_0101
    ),
    # check carry flag is cleared
    BinaryInputs(
        status_register=StatusRegister(c=True),
        src=0x7FFF_FFFF,
        dst=0x7181_7181),
])

OR_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    BinaryInputs(src=0x53, dst=0x35),  # check operation is something like logical and
    BinaryInputs(src=0x5353_5353, dst=0x0000_0035),  # check byte operation on register
    # check x flag doesn't influence result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x02, dst=0x01),
    BinaryInputs(src=0x80, dst=0xFF),  # check negative flag
    BinaryInputs(src=0x00, dst=0x00),  # check trivial zero flag
    # check overflow flag is cleared
    BinaryInputs(status_register=StatusRegister(v=True), src=0x7E, dst=0x01),
    # check carry flag is cleared
    BinaryInputs(status_register=StatusRegister(c=True), src=0x7E, dst=0x71),
])

OR_WORD_INPUTS = WordInstructionInputs(inputs=[
    # check operation is something like logical and
    BinaryInputs(src=0x3553, dst=0x5335),
    BinaryInputs(src=0x5353_5353, dst=0x0000_5335),  # check word operation on register
    # check x flag doesn't influence result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x0202, dst=0x0101),
    BinaryInputs(src=0x8000, dst=0x0000),  # check negative flag
    BinaryInputs(src=0x0000, dst=0x0000),  # check trivial zero flag
    # check overflow flag is cleared
    BinaryInputs(status_register=StatusRegister(v=True), src=0x7E00, dst=0x0100),
    # check carry flag is cleared
    BinaryInputs(status_register=StatusRegister(c=True), src=0x7E00, dst=0x7100),
])

OR_LONG_INPUTS = LongInstructionInputs(inputs=[
    # check operation is something like logical and
    BinaryInputs(src=0xA5553553, dst=0x5A555335),
    # check x flag doesn't influence result
    BinaryInputs(
        status_register=StatusRegister(x=True),
        src=0x0202_0202,
        dst=0x0101_0101
    ),
    BinaryInputs(src=0x8000_0000, dst=0x0000_0000),  # check negative flag
    BinaryInputs(src=0x0000_0000, dst=0x0000_0000),  # check trivial zero flag
    # check overflow flag is cleared
    BinaryInputs(
        status_register=StatusRegister(v=True),
        src=0x7E00_0000,
        dst=0x0100_0000
    ),
    # check carry flag is cleared
    BinaryInputs(
        status_register=StatusRegister(c=True),
        src=0x7E00_0000,
        dst=0x7100_0000
    ),
])

EOR_BYTE_INPUTS = ByteInstructionInputs(inputs=[
    BinaryInputs(src=0x53, dst=0x35),  # check operation is something like logical eor
    BinaryInputs(src=0x5353_5353, dst=0x00FF_0035),  # check byte operation on register
    # check x flag doesn't influence result
    BinaryInputs(status_register=StatusRegister(x=True), src=0xFF, dst=0xAA),
    BinaryInputs(src=0x80, dst=0x00),  # check negative flag
    BinaryInputs(src=0x00, dst=0x00),  # check trivial zero flag
    BinaryInputs(src=0x76, dst=0x76),  # check non-trivial zero flag
    # check overflow flag is cleared
    BinaryInputs(status_register=StatusRegister(v=True), src=0x7E, dst=0x01),
    # check carry flag is cleared
    BinaryInputs(status_register=StatusRegister(c=True), src=0x7E, dst=0x71),
])

EOR_WORD_INPUTS = WordInstructionInputs(inputs=[
    # check operation is something like logical eor
    BinaryInputs(src=0x3553, dst=0x5335),
    BinaryInputs(src=0x5353_5353, dst=0x00FF_5335),  # check word operation on register
    # check x flag doesn't influence result
    BinaryInputs(status_register=StatusRegister(x=True), src=0x0202, dst=0x0101),
    BinaryInputs(src=0x0000, dst=0x8000),  # check negative flag
    BinaryInputs(src=0x0000, dst=0x0000),  # check trivial zero flag
    BinaryInputs(src=0x3883, dst=0x3883),  # check non-trivial zero flag
    # check overflow flag is cleared
    BinaryInputs(status_register=StatusRegister(v=True), src=0x7E00, dst=0x0100),
    # check carry flag is cleared
    BinaryInputs(status_register=StatusRegister(c=True), src=0x7E00, dst=0x7100),
])

EOR_LONG_INPUTS = LongInstructionInputs(inputs=[
    # check operation is something like logical eor
    BinaryInputs(src=0xA5553553, dst=0x5A555335),
    # check x flag doesn't influence result
    BinaryInputs(
        status_register=StatusRegister(x=True),
        src=0x0202_0202,
        dst=0x0101_0101
    ),
    BinaryInputs(src=0x0000_0000, dst=0x8000_0000),  # check negative flag
    BinaryInputs(src=0x0000_0000, dst=0x0000_0000),  # check trivial zero flag
    BinaryInputs(src=0xBBBB_CCCC, dst=0xBBBB_CCCC),  # check non-trivial zero flag
    # check overflow flag is cleared
    BinaryInputs(
        status_register=StatusRegister(v=True),
        src=0x7E00_0000,
        dst=0x0100_0000
    ),
    # check carry flag is cleared
    BinaryInputs(
        status_register=StatusRegister(c=True),
        src=0x7E00_0000,
        dst=0x7100_0000
    ),
])

MULU_WORD_INPUTS = WordInstructionInputs(inputs=[
    # check operation is something like multiply
    BinaryInputs(src=0xA5A5_0007, dst=0xA5A5_0005),
    # check x flag doesn't influence result
    BinaryInputs(
        status_register=StatusRegister(x=True),
        src=0xA5A5_0007,
        dst=0xA5A5_0005
    ),
    BinaryInputs(src=0x0000_FFFF, dst=0x0000_FFFF),  # check negative flag
    BinaryInputs(src=0x0000_0000, dst=0x0000_0000),  # check trivial zero flag
    BinaryInputs(src=0xBBBB_CCCC, dst=0xBBBB_0000),  # check non-trivial zero flag
    # check overflow flag is cleared
    BinaryInputs(
        status_register=StatusRegister(v=True),
        src=0x7E00_0040,
        dst=0x0100_0080
    ),
    # check carry flag is cleared
    BinaryInputs(
        status_register=StatusRegister(c=True),
        src=0x7E00_0040,
        dst=0x7100_0080
    ),
    BinaryInputs(src=0x0000_8001, dst=0x0000_0001),  # check signed behaviour
    BinaryInputs(src=0x0000_0000, dst=0x0000_AAAA),  # check timings
    BinaryInputs(src=0x0000_FFFF, dst=0x0000_0001),
    BinaryInputs(src=0x0000_5555, dst=0x0000_0001),
    BinaryInputs(src=0x0000_AAAA, dst=0x0000_0001),
    BinaryInputs(src=0x0000_1010, dst=0x0000_0001),
])

DIVU_WORD_INPUTS = WordInstructionInputs(inputs=[
    # check operation is something like division
    BinaryInputs(src=0xA5A5_000D, dst=0x0000_03AD),
    # check x flag doesn't influence result
    BinaryInputs(
        status_register=StatusRegister(x=True),
        src=0xA5A5_000D,
        dst=0x0000_03AD
    ),
    BinaryInputs(
        status_register=StatusRegister(n=True),
        src=0x0000_0001,
        dst=0x0000_EFFF),  # check negative flag
    BinaryInputs(src=0x0000_0001, dst=0x0000_FFFF),  # check negative flag
    BinaryInputs(src=0x0000_0001, dst=0x0000_0000),  # check zero flag
    # check overflow flag is cleared
    BinaryInputs(
        status_register=StatusRegister(v=True),
        src=0x7E00_0200,
        dst=0x0100_0080
    ),
    # check carry flag is cleared
    BinaryInputs(
        status_register=StatusRegister(c=True),
        src=0x7E00_7200,
        dst=0x7100_0080
    ),
    BinaryInputs(src=0x0000_8000, dst=0x0000_0001),  # check signed behaviour
    BinaryInputs(src=0x0000_8001, dst=0x8000_0000),
    BinaryInputs(src=0x0000_FFFC, dst=0xFFFF_FFF7),
    BinaryInputs(src=0x0000_FFFC, dst=0x0000_ABCD),
    BinaryInputs(src=0x0000_000B, dst=0xFFFF_ABCD),
    BinaryInputs(src=0x0000_0001, dst=0x0000_AAAA),  # check timings
    BinaryInputs(src=0x0000_0001, dst=0x0000_5555),
    BinaryInputs(src=0x0000_0025, dst=0x0000_AAAA),  # prime divisor
    BinaryInputs(src=0x0000_0025, dst=0x0000_5555),
    BinaryInputs(src=0x0000_00B3, dst=0x0000_01C1),  # prime dividend and divisor
    BinaryInputs(src=0x0000_FFFC, dst=0x0FFF_FFF7),  # large dividend and divisor
    # check that the overflow flag gets set
    BinaryInputs(
        status_register=StatusRegister(v=False),
        src=0x0000_000D,
        dst=0x000E_03AD),
    BinaryInputs(
        status_register=StatusRegister(v=True),
        src=0x0000_000D,
        dst=0x000E_03AD),
    # check carry flag is cleared when overflow occurs
    BinaryInputs(
        status_register=StatusRegister(c=True),
        src=0x7E00_0200,
        dst=0x210F_0080
    ),
    BinaryInputs(src=0x0000_FFFF, dst=0x8000_0000),  # checks for early overflow in signed division
    BinaryInputs(src=0x0000_0001, dst=0x000_10000),
    BinaryInputs(src=0x0000_0001, dst=0xFFF1_0000),
    BinaryInputs(src=0x0000_0001, dst=0x0000_8000),  # checks for late overflow in signed division
    BinaryInputs(src=0x0000_0001, dst=0xFFFF_0001),
    BinaryInputs(src=0x0000_8000, dst=0x4000_8000),
    BinaryInputs(src=0x0000_8000, dst=0x8000_0001),
])
