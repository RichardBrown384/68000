"""
This module contains test file descriptions for the 
shift rotate right instructions.
"""

from .shift_rotate_shared import \
    shift_rotate_count_modes_and_cycles, \
    shift_rotate_register_modes_and_cycles, \
    shift_rotate_memory_modes_and_cycles

from ..inputs.shift_rotate_right import \
    ASR_BYTE_COUNT_INPUTS, \
    ASR_WORD_COUNT_INPUTS, \
    ASR_LONG_COUNT_INPUTS, \
    ASR_BYTE_REGISTER_INPUTS, \
    ASR_WORD_REGISTER_INPUTS, \
    ASR_LONG_REGISTER_INPUTS, \
    ASR_WORD_MEMORY_INPUTS, \
    LSR_BYTE_COUNT_INPUTS, \
    LSR_WORD_COUNT_INPUTS, \
    LSR_LONG_COUNT_INPUTS, \
    LSR_BYTE_REGISTER_INPUTS, \
    LSR_WORD_REGISTER_INPUTS, \
    LSR_LONG_REGISTER_INPUTS, \
    LSR_WORD_MEMORY_INPUTS, \
    ROXR_BYTE_COUNT_INPUTS, \
    ROXR_WORD_COUNT_INPUTS, \
    ROXR_LONG_COUNT_INPUTS, \
    ROXR_BYTE_REGISTER_INPUTS, \
    ROXR_WORD_REGISTER_INPUTS, \
    ROXR_LONG_REGISTER_INPUTS, \
    ROXR_WORD_MEMORY_INPUTS, \
    ROR_BYTE_COUNT_INPUTS, \
    ROR_WORD_COUNT_INPUTS, \
    ROR_LONG_COUNT_INPUTS, \
    ROR_BYTE_REGISTER_INPUTS, \
    ROR_WORD_REGISTER_INPUTS, \
    ROR_LONG_REGISTER_INPUTS, \
    ROR_WORD_MEMORY_INPUTS
from ..outputs.shift_rotate import \
    produce_asr_outputs, produce_lsr_outputs, \
    produce_roxr_outputs, produce_ror_outputs
from ..types.sized_instruction_test_file import SizedInstructionTestFile

ASR_BYTE_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ASR.B',
    name='asr_byte_count_to_data_register',
    inputs=ASR_BYTE_COUNT_INPUTS,
    outputs_producer=produce_asr_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=6)
)

ASR_WORD_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ASR.W',
    name='asr_word_count_to_data_register',
    inputs=ASR_WORD_COUNT_INPUTS,
    outputs_producer=produce_asr_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=6)
)

ASR_LONG_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ASR.L',
    name='asr_long_count_to_data_register',
    inputs=ASR_LONG_COUNT_INPUTS,
    outputs_producer=produce_asr_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=8)
)

ASR_BYTE_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ASR.B',
    name='asr_byte_register_to_data_register',
    inputs=ASR_BYTE_REGISTER_INPUTS,
    outputs_producer=produce_asr_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=6)
)

ASR_WORD_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ASR.W',
    name='asr_word_register_to_data_register',
    inputs=ASR_WORD_REGISTER_INPUTS,
    outputs_producer=produce_asr_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=6)
)

ASR_LONG_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ASR.L',
    name='asr_long_register_to_data_register',
    inputs=ASR_LONG_REGISTER_INPUTS,
    outputs_producer=produce_asr_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=8)
)

ASR_WORD_MEMORY = SizedInstructionTestFile(
    instruction='ASR.W',
    name='asr_word_to_memory',
    inputs=ASR_WORD_MEMORY_INPUTS,
    outputs_producer=produce_asr_outputs,
    modes=shift_rotate_memory_modes_and_cycles(memory_to_memory=8)
)

LSR_BYTE_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='LSR.B',
    name='lsr_byte_count_to_data_register',
    inputs=LSR_BYTE_COUNT_INPUTS,
    outputs_producer=produce_lsr_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=6)
)

LSR_WORD_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='LSR.W',
    name='lsr_word_count_to_data_register',
    inputs=LSR_WORD_COUNT_INPUTS,
    outputs_producer=produce_lsr_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=6)
)

LSR_LONG_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='LSR.L',
    name='lsr_long_count_to_data_register',
    inputs=LSR_LONG_COUNT_INPUTS,
    outputs_producer=produce_lsr_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=8)
)

LSR_BYTE_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='LSR.B',
    name='lsr_byte_register_to_data_register',
    inputs=LSR_BYTE_REGISTER_INPUTS,
    outputs_producer=produce_lsr_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=6)
)

LSR_WORD_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='LSR.W',
    name='lsr_word_register_to_data_register',
    inputs=LSR_WORD_REGISTER_INPUTS,
    outputs_producer=produce_lsr_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=6)
)

LSR_LONG_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='LSR.L',
    name='lsr_long_register_to_data_register',
    inputs=LSR_LONG_REGISTER_INPUTS,
    outputs_producer=produce_lsr_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=8)
)

LSR_WORD_MEMORY = SizedInstructionTestFile(
    instruction='LSR.W',
    name='lsr_word_to_memory',
    inputs=LSR_WORD_MEMORY_INPUTS,
    outputs_producer=produce_lsr_outputs,
    modes=shift_rotate_memory_modes_and_cycles(memory_to_memory=8)
)

ROXR_BYTE_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROXR.B',
    name='roxr_byte_count_to_data_register',
    inputs=ROXR_BYTE_COUNT_INPUTS,
    outputs_producer=produce_roxr_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=6)
)

ROXR_WORD_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROXR.W',
    name='roxr_word_count_to_data_register',
    inputs=ROXR_WORD_COUNT_INPUTS,
    outputs_producer=produce_roxr_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=6)
)

ROXR_LONG_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROXR.L',
    name='roxr_long_count_to_data_register',
    inputs=ROXR_LONG_COUNT_INPUTS,
    outputs_producer=produce_roxr_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=8)
)

ROXR_BYTE_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROXR.B',
    name='roxr_byte_register_to_data_register',
    inputs=ROXR_BYTE_REGISTER_INPUTS,
    outputs_producer=produce_roxr_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=6)
)

ROXR_WORD_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROXR.W',
    name='roxr_word_register_to_data_register',
    inputs=ROXR_WORD_REGISTER_INPUTS,
    outputs_producer=produce_roxr_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=6)
)

ROXR_LONG_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROXR.L',
    name='roxr_long_register_to_data_register',
    inputs=ROXR_LONG_REGISTER_INPUTS,
    outputs_producer=produce_roxr_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=8)
)

ROXR_WORD_MEMORY = SizedInstructionTestFile(
    instruction='ROXR.W',
    name='roxr_word_to_memory',
    inputs=ROXR_WORD_MEMORY_INPUTS,
    outputs_producer=produce_roxr_outputs,
    modes=shift_rotate_memory_modes_and_cycles(memory_to_memory=8)
)

ROR_BYTE_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROR.B',
    name='ror_byte_count_to_data_register',
    inputs=ROR_BYTE_COUNT_INPUTS,
    outputs_producer=produce_ror_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=6)
)

ROR_WORD_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROR.W',
    name='ror_word_count_to_data_register',
    inputs=ROR_WORD_COUNT_INPUTS,
    outputs_producer=produce_ror_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=6)
)

ROR_LONG_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROR.L',
    name='ror_long_count_to_data_register',
    inputs=ROR_LONG_COUNT_INPUTS,
    outputs_producer=produce_ror_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=8)
)

ROR_BYTE_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROR.B',
    name='ror_byte_register_to_data_register',
    inputs=ROR_BYTE_REGISTER_INPUTS,
    outputs_producer=produce_ror_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=6)
)

ROR_WORD_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROR.W',
    name='ror_word_register_to_data_register',
    inputs=ROR_WORD_REGISTER_INPUTS,
    outputs_producer=produce_ror_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=6)
)

ROR_LONG_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROR.L',
    name='ror_long_register_to_data_register',
    inputs=ROR_LONG_REGISTER_INPUTS,
    outputs_producer=produce_ror_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=8)
)

ROR_WORD_MEMORY = SizedInstructionTestFile(
    instruction='ROR.W',
    name='ror_word_to_memory',
    inputs=ROR_WORD_MEMORY_INPUTS,
    outputs_producer=produce_ror_outputs,
    modes=shift_rotate_memory_modes_and_cycles(memory_to_memory=8)
)
