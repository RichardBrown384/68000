"""
This module contains test file descriptions for the immediate instructions.
"""

from typing import List

from ..inputs.arithmetic import \
    ADD_BYTE_INPUTS, ADD_WORD_INPUTS, ADD_LONG_INPUTS, \
    SUB_BYTE_INPUTS, SUB_WORD_INPUTS, SUB_LONG_INPUTS, \
    CMP_BYTE_INPUTS, CMP_WORD_INPUTS, CMP_LONG_INPUTS, \
    AND_BYTE_INPUTS, AND_WORD_INPUTS, AND_LONG_INPUTS, \
    OR_BYTE_INPUTS, OR_WORD_INPUTS, OR_LONG_INPUTS, \
    EOR_BYTE_INPUTS, EOR_WORD_INPUTS, EOR_LONG_INPUTS
from ..address_mode_data.immediate import \
    IMMEDIATE_TO_DATA_REGISTER, \
    IMMEDIATE_TO_MEMORY
from ..outputs.arithmetic import \
    produce_add_outputs, produce_sub_outputs, \
    produce_cmp_outputs, produce_and_outputs, \
    produce_or_outputs, produce_eor_outputs
from ..types.cycles import \
    takes_n_cycles, \
    takes_n_cycles_plus_destination
from ..types.sized_instruction_test_file import \
    SizedInstructionTestFile, \
    ModesAndCycles


def __modes_and_cycles(
        immediate_to_register: int = 0,
        immediate_to_memory: int = 0) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(address_modes=[
            IMMEDIATE_TO_DATA_REGISTER
        ], cycles=takes_n_cycles(immediate_to_register)),
        ModesAndCycles(address_modes=[
            IMMEDIATE_TO_MEMORY
        ], cycles=takes_n_cycles_plus_destination(immediate_to_memory))
    ]


ADDI_BYTE = SizedInstructionTestFile(
    instruction='ADDI.B',
    name='addi_byte',
    inputs=ADD_BYTE_INPUTS,
    outputs_producer=produce_add_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=8,
        immediate_to_memory=12)
)

ADDI_WORD = SizedInstructionTestFile(
    instruction='ADDI.W',
    name='addi_word',
    inputs=ADD_WORD_INPUTS,
    outputs_producer=produce_add_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=8,
        immediate_to_memory=12)
)

ADDI_LONG = SizedInstructionTestFile(
    instruction='ADDI.L',
    name='addi_long',
    inputs=ADD_LONG_INPUTS,
    outputs_producer=produce_add_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=16,
        immediate_to_memory=20)
)

SUBI_BYTE = SizedInstructionTestFile(
    instruction='SUBI.B',
    name='subi_byte',
    inputs=SUB_BYTE_INPUTS,
    outputs_producer=produce_sub_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=8,
        immediate_to_memory=12)
)

SUBI_WORD = SizedInstructionTestFile(
    instruction='SUBI.W',
    name='subi_word',
    inputs=SUB_WORD_INPUTS,
    outputs_producer=produce_sub_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=8,
        immediate_to_memory=12)
)

SUBI_LONG = SizedInstructionTestFile(
    instruction='SUBI.L',
    name='subi_long',
    inputs=SUB_LONG_INPUTS,
    outputs_producer=produce_sub_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=16,
        immediate_to_memory=20)
)

CMPI_BYTE = SizedInstructionTestFile(
    instruction='CMPI.B',
    name='cmpi_byte',
    inputs=CMP_BYTE_INPUTS,
    outputs_producer=produce_cmp_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=8,
        immediate_to_memory=8)
)

CMPI_WORD = SizedInstructionTestFile(
    instruction='CMPI.W',
    name='cmpi_word',
    inputs=CMP_WORD_INPUTS,
    outputs_producer=produce_cmp_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=8,
        immediate_to_memory=8)
)

CMPI_LONG = SizedInstructionTestFile(
    instruction='CMPI.L',
    name='cmpi_long',
    inputs=CMP_LONG_INPUTS,
    outputs_producer=produce_cmp_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=14,
        immediate_to_memory=12)
)

ANDI_BYTE = SizedInstructionTestFile(
    instruction='ANDI.B',
    name='andi_byte',
    inputs=AND_BYTE_INPUTS,
    outputs_producer=produce_and_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=8,
        immediate_to_memory=12)
)

ANDI_WORD = SizedInstructionTestFile(
    instruction='ANDI.W',
    name='andi_word',
    inputs=AND_WORD_INPUTS,
    outputs_producer=produce_and_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=8,
        immediate_to_memory=12)
)

ANDI_LONG = SizedInstructionTestFile(
    instruction='ANDI.L',
    name='andi_long',
    inputs=AND_LONG_INPUTS,
    outputs_producer=produce_and_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=16,
        immediate_to_memory=20)
)

ORI_BYTE = SizedInstructionTestFile(
    instruction='ORI.B',
    name='ori_byte',
    inputs=OR_BYTE_INPUTS,
    outputs_producer=produce_or_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=8,
        immediate_to_memory=12)
)

ORI_WORD = SizedInstructionTestFile(
    instruction='ORI.W',
    name='ori_word',
    inputs=OR_WORD_INPUTS,
    outputs_producer=produce_or_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=8,
        immediate_to_memory=12)
)

ORI_LONG = SizedInstructionTestFile(
    instruction='ORI.L',
    name='ori_long',
    inputs=OR_LONG_INPUTS,
    outputs_producer=produce_or_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=16,
        immediate_to_memory=20)
)

EORI_BYTE = SizedInstructionTestFile(
    instruction='EORI.B',
    name='eori_byte',
    inputs=EOR_BYTE_INPUTS,
    outputs_producer=produce_eor_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=8,
        immediate_to_memory=12)
)

EORI_WORD = SizedInstructionTestFile(
    instruction='EORI.W',
    name='eori_word',
    inputs=EOR_WORD_INPUTS,
    outputs_producer=produce_eor_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=8,
        immediate_to_memory=12)
)

EORI_LONG = SizedInstructionTestFile(
    instruction='EORI.L',
    name='eori_long',
    inputs=EOR_LONG_INPUTS,
    outputs_producer=produce_eor_outputs,
    modes=__modes_and_cycles(
        immediate_to_register=16,
        immediate_to_memory=20)

)
