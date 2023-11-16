"""
This module contains test file descriptions for the
shift rotate left instructions.
"""

from .shift_rotate_shared import \
    shift_rotate_count_modes_and_cycles, \
    shift_rotate_register_modes_and_cycles, \
    shift_rotate_memory_modes_and_cycles

from ..inputs.shift_rotate_left import \
    ASL_BYTE_COUNT_INPUTS, \
    ASL_WORD_COUNT_INPUTS, \
    ASL_LONG_COUNT_INPUTS, \
    ASL_BYTE_REGISTER_INPUTS, \
    ASL_WORD_REGISTER_INPUTS, \
    ASL_LONG_REGISTER_INPUTS, \
    ASL_WORD_MEMORY_INPUTS, \
    LSL_BYTE_COUNT_INPUTS, \
    LSL_WORD_COUNT_INPUTS, \
    LSL_LONG_COUNT_INPUTS, \
    LSL_BYTE_REGISTER_INPUTS, \
    LSL_WORD_REGISTER_INPUTS, \
    LSL_LONG_REGISTER_INPUTS, \
    LSL_WORD_MEMORY_INPUTS, \
    ROXL_BYTE_COUNT_INPUTS, \
    ROXL_WORD_COUNT_INPUTS, \
    ROXL_LONG_COUNT_INPUTS, \
    ROXL_BYTE_REGISTER_INPUTS, \
    ROXL_WORD_REGISTER_INPUTS, \
    ROXL_LONG_REGISTER_INPUTS, \
    ROXL_WORD_MEMORY_INPUTS, \
    ROL_BYTE_COUNT_INPUTS, \
    ROL_WORD_COUNT_INPUTS, \
    ROL_LONG_COUNT_INPUTS, \
    ROL_BYTE_REGISTER_INPUTS, \
    ROL_WORD_REGISTER_INPUTS, \
    ROL_LONG_REGISTER_INPUTS, \
    ROL_WORD_MEMORY_INPUTS
from ..outputs.shift_rotate import \
    produce_asl_outputs, produce_lsl_outputs, \
    produce_roxl_outputs, produce_rol_outputs
from ..types.sized_instruction_test_file import SizedInstructionTestFile

ASL_BYTE_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ASL.B',
    name='asl_byte_count_to_data_register',
    inputs=ASL_BYTE_COUNT_INPUTS,
    outputs_producer=produce_asl_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=6)
)

ASL_WORD_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ASL.W',
    name='asl_word_count_to_data_register',
    inputs=ASL_WORD_COUNT_INPUTS,
    outputs_producer=produce_asl_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=6)
)

ASL_LONG_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ASL.L',
    name='asl_long_count_to_data_register',
    inputs=ASL_LONG_COUNT_INPUTS,
    outputs_producer=produce_asl_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=8)
)

ASL_BYTE_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ASL.B',
    name='asl_byte_register_to_data_register',
    inputs=ASL_BYTE_REGISTER_INPUTS,
    outputs_producer=produce_asl_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=6)
)

ASL_WORD_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ASL.W',
    name='asl_word_register_to_data_register',
    inputs=ASL_WORD_REGISTER_INPUTS,
    outputs_producer=produce_asl_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=6)
)

ASL_LONG_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ASL.L',
    name='asl_long_register_to_data_register',
    inputs=ASL_LONG_REGISTER_INPUTS,
    outputs_producer=produce_asl_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=8)
)

ASL_WORD_MEMORY = SizedInstructionTestFile(
    instruction='ASL.W',
    name='asl_word_to_memory',
    inputs=ASL_WORD_MEMORY_INPUTS,
    outputs_producer=produce_asl_outputs,
    modes=shift_rotate_memory_modes_and_cycles(memory_to_memory=8)
)

LSL_BYTE_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='LSL.B',
    name='lsl_byte_count_to_data_register',
    inputs=LSL_BYTE_COUNT_INPUTS,
    outputs_producer=produce_lsl_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=6)
)

LSL_WORD_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='LSL.W',
    name='lsl_word_count_to_data_register',
    inputs=LSL_WORD_COUNT_INPUTS,
    outputs_producer=produce_lsl_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=6)
)

LSL_LONG_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='LSL.L',
    name='lsl_long_count_to_data_register',
    inputs=LSL_LONG_COUNT_INPUTS,
    outputs_producer=produce_lsl_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=8)
)

LSL_BYTE_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='LSL.B',
    name='lsl_byte_register_to_data_register',
    inputs=LSL_BYTE_REGISTER_INPUTS,
    outputs_producer=produce_lsl_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=6)
)

LSL_WORD_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='LSL.W',
    name='lsl_word_register_to_data_register',
    inputs=LSL_WORD_REGISTER_INPUTS,
    outputs_producer=produce_lsl_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=6)
)

LSL_LONG_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='LSL.L',
    name='lsl_long_register_to_data_register',
    inputs=LSL_LONG_REGISTER_INPUTS,
    outputs_producer=produce_lsl_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=8)
)

LSL_WORD_MEMORY = SizedInstructionTestFile(
    instruction='LSL.W',
    name='lsl_word_to_memory',
    inputs=LSL_WORD_MEMORY_INPUTS,
    outputs_producer=produce_lsl_outputs,
    modes=shift_rotate_memory_modes_and_cycles(memory_to_memory=8)
)

ROXL_BYTE_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROXL.B',
    name='roxl_byte_count_to_data_register',
    inputs=ROXL_BYTE_COUNT_INPUTS,
    outputs_producer=produce_roxl_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=6)
)

ROXL_WORD_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROXL.W',
    name='roxl_word_count_to_data_register',
    inputs=ROXL_WORD_COUNT_INPUTS,
    outputs_producer=produce_roxl_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=6)
)

ROXL_LONG_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROXL.L',
    name='roxl_long_count_to_data_register',
    inputs=ROXL_LONG_COUNT_INPUTS,
    outputs_producer=produce_roxl_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=8)
)

ROXL_BYTE_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROXL.B',
    name='roxl_byte_register_to_data_register',
    inputs=ROXL_BYTE_REGISTER_INPUTS,
    outputs_producer=produce_roxl_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=6)
)

ROXL_WORD_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROXL.W',
    name='roxl_word_register_to_data_register',
    inputs=ROXL_WORD_REGISTER_INPUTS,
    outputs_producer=produce_roxl_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=6)
)

ROXL_LONG_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROXL.L',
    name='roxl_long_register_to_data_register',
    inputs=ROXL_LONG_REGISTER_INPUTS,
    outputs_producer=produce_roxl_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=8)
)

ROXL_WORD_MEMORY = SizedInstructionTestFile(
    instruction='ROXL.W',
    name='roxl_word_to_memory',
    inputs=ROXL_WORD_MEMORY_INPUTS,
    outputs_producer=produce_roxl_outputs,
    modes=shift_rotate_memory_modes_and_cycles(memory_to_memory=8)
)

ROL_BYTE_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROL.B',
    name='rol_byte_count_to_data_register',
    inputs=ROL_BYTE_COUNT_INPUTS,
    outputs_producer=produce_rol_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=6)
)

ROL_WORD_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROL.W',
    name='rol_word_count_to_data_register',
    inputs=ROL_WORD_COUNT_INPUTS,
    outputs_producer=produce_rol_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=6)
)

ROL_LONG_COUNT_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROL.L',
    name='rol_long_count_to_data_register',
    inputs=ROL_LONG_COUNT_INPUTS,
    outputs_producer=produce_rol_outputs,
    modes=shift_rotate_count_modes_and_cycles(immediate_to_register=8)
)

ROL_BYTE_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROL.B',
    name='rol_byte_register_to_data_register',
    inputs=ROL_BYTE_REGISTER_INPUTS,
    outputs_producer=produce_rol_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=6)
)

ROL_WORD_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROL.W',
    name='rol_word_register_to_data_register',
    inputs=ROL_WORD_REGISTER_INPUTS,
    outputs_producer=produce_rol_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=6)
)

ROL_LONG_REGISTER_DATA_REGISTER = SizedInstructionTestFile(
    instruction='ROL.L',
    name='rol_long_register_to_data_register',
    inputs=ROL_LONG_REGISTER_INPUTS,
    outputs_producer=produce_rol_outputs,
    modes=shift_rotate_register_modes_and_cycles(register_to_register=8)
)

ROL_WORD_MEMORY = SizedInstructionTestFile(
    instruction='ROL.W',
    name='rol_word_to_memory',
    inputs=ROL_WORD_MEMORY_INPUTS,
    outputs_producer=produce_rol_outputs,
    modes=shift_rotate_memory_modes_and_cycles(memory_to_memory=8)
)
