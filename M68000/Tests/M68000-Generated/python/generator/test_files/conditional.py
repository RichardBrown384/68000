"""
This module contains test file descriptions for the
conditional instructions.
"""

from ..address_mode_data.conditional import \
    CONDITIONAL_WORD_DECREMENT_AND_BRANCH, \
    CONDITIONAL_BYTE_BRANCH, \
    CONDITIONAL_WORD_BRANCH, \
    CONDITIONAL_BYTE_SUBROUTINE_BRANCH,\
    CONDITIONAL_WORD_SUBROUTINE_BRANCH
from ..inputs.conditional import \
    DBT_WORD_INPUTS, DBF_WORD_INPUTS, \
    DBHI_WORD_INPUTS, DBLS_WORD_INPUTS, \
    DBCC_WORD_INPUTS, DBCS_WORD_INPUTS, \
    DBNE_WORD_INPUTS, DBEQ_WORD_INPUTS, \
    DBVC_WORD_INPUTS, DBVS_WORD_INPUTS, \
    DBPL_WORD_INPUTS, DBMI_WORD_INPUTS, \
    DBGE_WORD_INPUTS, DBLT_WORD_INPUTS, \
    DBGT_WORD_INPUTS, DBLE_WORD_INPUTS, \
    BRA_BYTE_INPUTS, \
    BHI_BYTE_INPUTS, BLS_BYTE_INPUTS, \
    BCC_BYTE_INPUTS, BCS_BYTE_INPUTS, \
    BNE_BYTE_INPUTS, BEQ_BYTE_INPUTS, \
    BVC_BYTE_INPUTS, BVS_BYTE_INPUTS, \
    BPL_BYTE_INPUTS, BMI_BYTE_INPUTS, \
    BGE_BYTE_INPUTS, BLT_BYTE_INPUTS, \
    BGT_BYTE_INPUTS, BLE_BYTE_INPUTS, \
    BRA_WORD_INPUTS, \
    BHI_WORD_INPUTS, BLS_WORD_INPUTS, \
    BCC_WORD_INPUTS, BCS_WORD_INPUTS, \
    BNE_WORD_INPUTS, BEQ_WORD_INPUTS, \
    BVC_WORD_INPUTS, BVS_WORD_INPUTS, \
    BPL_WORD_INPUTS, BMI_WORD_INPUTS, \
    BGE_WORD_INPUTS, BLT_WORD_INPUTS, \
    BGT_WORD_INPUTS, BLE_WORD_INPUTS, \
    BSR_BYTE_INPUTS, \
    BSR_WORD_INPUTS
from ..outputs.conditional import produce_dbcc_outputs, produce_bcc_outputs
from ..types.cycles import takes_n_cycles_plus_destination
from ..types.sized_instruction_inputs import WordInstructionInputs, ByteInstructionInputs
from ..types.sized_instruction_test_file import \
    SizedInstructionTestFile, \
    ModesAndCycles


def __create_dbcc_test_file(
        instruction: str,
        inputs: WordInstructionInputs) -> SizedInstructionTestFile:
    return SizedInstructionTestFile(
        instruction=instruction,
        name=f'{instruction.lower()}_word',
        inputs=inputs,
        outputs_producer=produce_dbcc_outputs,
        modes=[ModesAndCycles(address_modes=[
            CONDITIONAL_WORD_DECREMENT_AND_BRANCH
        ], cycles=takes_n_cycles_plus_destination(0))]
    )


def __create_bcc_byte_test_file(
        instruction: str,
        inputs: ByteInstructionInputs) -> SizedInstructionTestFile:
    return SizedInstructionTestFile(
        instruction=f'{instruction}.B',
        name=f'{instruction.lower()}_byte',
        inputs=inputs,
        outputs_producer=produce_bcc_outputs,
        modes=[ModesAndCycles(address_modes=[
            CONDITIONAL_BYTE_BRANCH
        ], cycles=takes_n_cycles_plus_destination(0))]
    )


def __create_bcc_word_test_file(
        instruction: str,
        inputs: WordInstructionInputs) -> SizedInstructionTestFile:
    return SizedInstructionTestFile(
        instruction=f'{instruction}.W',
        name=f'{instruction.lower()}_word',
        inputs=inputs,
        outputs_producer=produce_bcc_outputs,
        modes=[ModesAndCycles(address_modes=[
            CONDITIONAL_WORD_BRANCH
        ], cycles=takes_n_cycles_plus_destination(0))]
    )


def __create_bsr_byte_test_file(
        inputs: ByteInstructionInputs) -> SizedInstructionTestFile:
    return SizedInstructionTestFile(
        instruction='BSR.B',
        name='bsr_byte',
        inputs=inputs,
        outputs_producer=produce_bcc_outputs,
        modes=[ModesAndCycles(address_modes=[
            CONDITIONAL_BYTE_SUBROUTINE_BRANCH
        ], cycles=takes_n_cycles_plus_destination(0))]
    )


def __create_bsr_word_test_file(
        inputs: WordInstructionInputs) -> SizedInstructionTestFile:
    return SizedInstructionTestFile(
        instruction='BSR.W',
        name='bsr_word',
        inputs=inputs,
        outputs_producer=produce_bcc_outputs,
        modes=[ModesAndCycles(address_modes=[
            CONDITIONAL_WORD_SUBROUTINE_BRANCH
        ], cycles=takes_n_cycles_plus_destination(0))]
    )


DBT_WORD = __create_dbcc_test_file('DBT', DBT_WORD_INPUTS)
DBF_WORD = __create_dbcc_test_file('DBF', DBF_WORD_INPUTS)
DBHI_WORD = __create_dbcc_test_file('DBHI', DBHI_WORD_INPUTS)
DBLS_WORD = __create_dbcc_test_file('DBLS', DBLS_WORD_INPUTS)
DBCC_WORD = __create_dbcc_test_file('DBCC', DBCC_WORD_INPUTS)
DBCS_WORD = __create_dbcc_test_file('DBCS', DBCS_WORD_INPUTS)
DBNE_WORD = __create_dbcc_test_file('DBNE', DBNE_WORD_INPUTS)
DBEQ_WORD = __create_dbcc_test_file('DBEQ', DBEQ_WORD_INPUTS)
DBVC_WORD = __create_dbcc_test_file('DBVC', DBVC_WORD_INPUTS)
DBVS_WORD = __create_dbcc_test_file('DBVS', DBVS_WORD_INPUTS)
DBPL_WORD = __create_dbcc_test_file('DBPL', DBPL_WORD_INPUTS)
DBMI_WORD = __create_dbcc_test_file('DBMI', DBMI_WORD_INPUTS)
DBGE_WORD = __create_dbcc_test_file('DBGE', DBGE_WORD_INPUTS)
DBLT_WORD = __create_dbcc_test_file('DBLT', DBLT_WORD_INPUTS)
DBGT_WORD = __create_dbcc_test_file('DBGT', DBGT_WORD_INPUTS)
DBLE_WORD = __create_dbcc_test_file('DBLE', DBLE_WORD_INPUTS)

BRA_BYTE = __create_bcc_byte_test_file('BRA', BRA_BYTE_INPUTS)
BHI_BYTE = __create_bcc_byte_test_file('BHI', BHI_BYTE_INPUTS)
BLS_BYTE = __create_bcc_byte_test_file('BLS', BLS_BYTE_INPUTS)
BCC_BYTE = __create_bcc_byte_test_file('BCC', BCC_BYTE_INPUTS)
BCS_BYTE = __create_bcc_byte_test_file('BCS', BCS_BYTE_INPUTS)
BNE_BYTE = __create_bcc_byte_test_file('BNE', BNE_BYTE_INPUTS)
BEQ_BYTE = __create_bcc_byte_test_file('BEQ', BEQ_BYTE_INPUTS)
BVC_BYTE = __create_bcc_byte_test_file('BVC', BVC_BYTE_INPUTS)
BVS_BYTE = __create_bcc_byte_test_file('BVS', BVS_BYTE_INPUTS)
BPL_BYTE = __create_bcc_byte_test_file('BPL', BPL_BYTE_INPUTS)
BMI_BYTE = __create_bcc_byte_test_file('BMI', BMI_BYTE_INPUTS)
BGE_BYTE = __create_bcc_byte_test_file('BGE', BGE_BYTE_INPUTS)
BLT_BYTE = __create_bcc_byte_test_file('BLT', BLT_BYTE_INPUTS)
BGT_BYTE = __create_bcc_byte_test_file('BGT', BGT_BYTE_INPUTS)
BLE_BYTE = __create_bcc_byte_test_file('BLE', BLE_BYTE_INPUTS)

BRA_WORD = __create_bcc_word_test_file('BRA', BRA_WORD_INPUTS)
BHI_WORD = __create_bcc_word_test_file('BHI', BHI_WORD_INPUTS)
BLS_WORD = __create_bcc_word_test_file('BLS', BLS_WORD_INPUTS)
BCC_WORD = __create_bcc_word_test_file('BCC', BCC_WORD_INPUTS)
BCS_WORD = __create_bcc_word_test_file('BCS', BCS_WORD_INPUTS)
BNE_WORD = __create_bcc_word_test_file('BNE', BNE_WORD_INPUTS)
BEQ_WORD = __create_bcc_word_test_file('BEQ', BEQ_WORD_INPUTS)
BVC_WORD = __create_bcc_word_test_file('BVC', BVC_WORD_INPUTS)
BVS_WORD = __create_bcc_word_test_file('BVS', BVS_WORD_INPUTS)
BPL_WORD = __create_bcc_word_test_file('BPL', BPL_WORD_INPUTS)
BMI_WORD = __create_bcc_word_test_file('BMI', BMI_WORD_INPUTS)
BGE_WORD = __create_bcc_word_test_file('BGE', BGE_WORD_INPUTS)
BLT_WORD = __create_bcc_word_test_file('BLT', BLT_WORD_INPUTS)
BGT_WORD = __create_bcc_word_test_file('BGT', BGT_WORD_INPUTS)
BLE_WORD = __create_bcc_word_test_file('BLE', BLE_WORD_INPUTS)

BSR_BYTE = __create_bsr_byte_test_file(BSR_BYTE_INPUTS)
BSR_WORD = __create_bsr_word_test_file(BSR_WORD_INPUTS)
