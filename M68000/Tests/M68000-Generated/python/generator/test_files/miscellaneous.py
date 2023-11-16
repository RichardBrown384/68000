"""
This module contains test file descriptions for the miscellaneous instructions.
"""
from ..types.cycles import \
    takes_n_cycles_plus_source, \
    takes_n_cycles_plus_destination, \
    takes_n_cycles
from ..address_mode_data.arithmetic import \
    BINARY_MEMORY_TO_DATA_REGISTER
from ..address_mode_data.miscellaneous import \
    MISCELLANEOUS_STATUS_REGISTER_TO_DATA_REGISTER, \
    MISCELLANEOUS_STATUS_REGISTER_TO_MEMORY, \
    MISCELLANEOUS_DATA_REGISTER_TO_CONDITION_CODE_REGISTER, \
    MISCELLANEOUS_DATA_REGISTER_TO_STATUS_REGISTER, \
    MISCELLANEOUS_MEMORY_TO_CONDITION_CODE_REGISTER, \
    MISCELLANEOUS_MEMORY_TO_STATUS_REGISTER, \
    MISCELLANEOUS_IMMEDIATE_TO_CONDITION_CODE_REGISTER, \
    MISCELLANEOUS_IMMEDIATE_TO_STATUS_REGISTER, \
    MISCELLANEOUS_IMMEDIATE_TO_NULL
from ..address_mode_data.single_operand import \
    SINGLE_TO_DATA_REGISTER
from ..inputs.miscellaneous import \
    LOGICAL_OPERATION_CONDITION_CODE_REGISTER_INPUTS, \
    LOGICAL_TO_STATUS_REGISTER_INPUTS, \
    MOVE_TO_CONDITION_CODE_STATUS_REGISTER_INPUTS, \
    MOVE_TO_STATUS_REGISTER_WORD_INPUTS, \
    MOVE_FROM_STATUS_REGISTER_INPUTS, \
    EXT_WORD_INPUTS, \
    EXT_LONG_INPUTS, \
    SWAP_INPUTS, \
    CHK_INPUTS, \
    STOP_INPUTS
from ..outputs.miscellaneous import \
    produce_andi_condition_code_register_outputs, \
    produce_eori_condition_code_register_outputs, \
    produce_ori_condition_code_register_outputs, \
    produce_andi_status_register_outputs, \
    produce_eori_status_register_outputs, \
    produce_ori_status_register_outputs, \
    produce_move_to_condition_code_register_outputs, \
    produce_move_to_status_register_outputs, \
    produce_move_from_status_register_outputs, \
    produce_ext_word_outputs, \
    produce_ext_long_outputs, \
    produce_swap_outputs, \
    produce_chk_outputs
from ..types.sized_instruction_test_file import \
    SizedInstructionTestFile, \
    ModesAndCycles


def __immediate_logical_condition_code_register_modes_and_cycles():
    return [
        ModesAndCycles(address_modes=[
            MISCELLANEOUS_IMMEDIATE_TO_CONDITION_CODE_REGISTER
        ], cycles=takes_n_cycles(20))
    ]


def __immediate_logical_status_register_modes_and_cycles():
    return [
        ModesAndCycles(address_modes=[
            MISCELLANEOUS_IMMEDIATE_TO_STATUS_REGISTER
        ], cycles=takes_n_cycles(20))
    ]


ANDI_CONDITION_CODE_REGISTER_BYTE = SizedInstructionTestFile(
    instruction='ANDI.B',
    name='andi_ccr_byte',
    inputs=LOGICAL_OPERATION_CONDITION_CODE_REGISTER_INPUTS,
    outputs_producer=produce_andi_condition_code_register_outputs,
    modes=__immediate_logical_condition_code_register_modes_and_cycles()
)

EORI_CONDITION_CODE_REGISTER_BYTE = SizedInstructionTestFile(
    instruction='EORI.B',
    name='eori_ccr_byte',
    inputs=LOGICAL_OPERATION_CONDITION_CODE_REGISTER_INPUTS,
    outputs_producer=produce_eori_condition_code_register_outputs,
    modes=__immediate_logical_condition_code_register_modes_and_cycles()
)

ORI_CONDITION_CODE_REGISTER_BYTE = SizedInstructionTestFile(
    instruction='ORI.B',
    name='ori_ccr_byte',
    inputs=LOGICAL_OPERATION_CONDITION_CODE_REGISTER_INPUTS,
    outputs_producer=produce_ori_condition_code_register_outputs,
    modes=__immediate_logical_condition_code_register_modes_and_cycles()
)

ANDI_STATUS_REGISTER_WORD = SizedInstructionTestFile(
    instruction='ANDI.W',
    name='andi_sr_word',
    inputs=LOGICAL_TO_STATUS_REGISTER_INPUTS,
    outputs_producer=produce_andi_status_register_outputs,
    modes=__immediate_logical_status_register_modes_and_cycles()
)

EORI_STATUS_REGISTER_WORD = SizedInstructionTestFile(
    instruction='EORI.W',
    name='eori_sr_word',
    inputs=LOGICAL_TO_STATUS_REGISTER_INPUTS,
    outputs_producer=produce_eori_status_register_outputs,
    modes=__immediate_logical_status_register_modes_and_cycles()
)

ORI_STATUS_REGISTER_WORD = SizedInstructionTestFile(
    instruction='ORI.W',
    name='ori_sr_word',
    inputs=LOGICAL_TO_STATUS_REGISTER_INPUTS,
    outputs_producer=produce_ori_status_register_outputs,
    modes=__immediate_logical_status_register_modes_and_cycles()
)

MOVE_TO_CONDITION_CODE_REGISTER = SizedInstructionTestFile(
    instruction='MOVE.W',
    name='move_to_ccr_word',
    inputs=MOVE_TO_CONDITION_CODE_STATUS_REGISTER_INPUTS,
    outputs_producer=produce_move_to_condition_code_register_outputs,
    modes=[
        ModesAndCycles(address_modes=[
            MISCELLANEOUS_DATA_REGISTER_TO_CONDITION_CODE_REGISTER,
            MISCELLANEOUS_MEMORY_TO_CONDITION_CODE_REGISTER,
            MISCELLANEOUS_IMMEDIATE_TO_CONDITION_CODE_REGISTER,
        ], cycles=takes_n_cycles_plus_source(12))
    ]
)

MOVE_TO_STATUS_REGISTER_WORD = SizedInstructionTestFile(
    instruction='MOVE.W',
    name='move_to_sr_word',
    inputs=MOVE_TO_STATUS_REGISTER_WORD_INPUTS,
    outputs_producer=produce_move_to_status_register_outputs,
    modes=[
        ModesAndCycles(address_modes=[
            MISCELLANEOUS_DATA_REGISTER_TO_STATUS_REGISTER,
            MISCELLANEOUS_MEMORY_TO_STATUS_REGISTER,
            MISCELLANEOUS_IMMEDIATE_TO_STATUS_REGISTER
        ], cycles=takes_n_cycles_plus_source(12))
    ]
)

MOVE_FROM_STATUS_REGISTER = SizedInstructionTestFile(
    instruction='MOVE.W',
    name='move_from_sr_word',
    inputs=MOVE_FROM_STATUS_REGISTER_INPUTS,
    outputs_producer=produce_move_from_status_register_outputs,
    modes=[
        ModesAndCycles(address_modes=[
            MISCELLANEOUS_STATUS_REGISTER_TO_DATA_REGISTER,
        ], cycles=takes_n_cycles(6)),
        ModesAndCycles(address_modes=[
            MISCELLANEOUS_STATUS_REGISTER_TO_MEMORY
        ], cycles=takes_n_cycles_plus_destination(8))
    ]
)

EXT_WORD = SizedInstructionTestFile(
    instruction='EXT.W',
    name='ext_word',
    inputs=EXT_WORD_INPUTS,
    outputs_producer=produce_ext_word_outputs,
    modes=[
        ModesAndCycles(address_modes=[
            SINGLE_TO_DATA_REGISTER,
        ], cycles=takes_n_cycles(4))
    ]
)

EXT_LONG = SizedInstructionTestFile(
    instruction='EXT.L',
    name='ext_long',
    inputs=EXT_LONG_INPUTS,
    outputs_producer=produce_ext_long_outputs,
    modes=[
        ModesAndCycles(address_modes=[
            SINGLE_TO_DATA_REGISTER,
        ], cycles=takes_n_cycles(4))
    ]
)

SWAP = SizedInstructionTestFile(
    instruction='SWAP',
    name='swap',
    inputs=SWAP_INPUTS,
    outputs_producer=produce_swap_outputs,
    modes=[
        ModesAndCycles(address_modes=[
            SINGLE_TO_DATA_REGISTER,
        ], cycles=takes_n_cycles(4))
    ]
)

CHK_WORD = SizedInstructionTestFile(
    instruction='CHK',
    name='chk_word',
    inputs=CHK_INPUTS,
    outputs_producer=produce_chk_outputs,
    modes=[
        ModesAndCycles(address_modes=[
            BINARY_MEMORY_TO_DATA_REGISTER,
        ], cycles=takes_n_cycles_plus_source(10))
    ]
)

STOP = SizedInstructionTestFile(
    instruction='STOP',
    name='stop',
    inputs=STOP_INPUTS,
    outputs_producer=produce_move_to_status_register_outputs,
    modes=[
        ModesAndCycles(address_modes=[
            MISCELLANEOUS_IMMEDIATE_TO_NULL
        ], cycles=takes_n_cycles(4))
    ]
)
