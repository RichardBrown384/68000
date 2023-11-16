"""
This module contains inputs for the conditional instructions.
"""
import itertools

from ..status_register_data import ALL_CONDITION_CODE_REGISTERS
from ..types.condition_code import ConditionCode
from ..types.instruction_inputs import ConditionalInputs
from ..types.sized_instruction_inputs import WordInstructionInputs, ByteInstructionInputs


def __create_dbcc_word_inputs(condition_code: ConditionCode) -> WordInstructionInputs:
    return WordInstructionInputs(inputs=[
        ConditionalInputs(status_register=status_register,
                          condition_code=condition_code,
                          dst=dst)
        for status_register, condition_code, dst in itertools.product(
            ALL_CONDITION_CODE_REGISTERS,
            [condition_code],
            # expired, about to expire, not-expired
            [0x0001_0000, 0x0001_0001, 0x0001_0231])
    ])


def __create_bcc_byte_inputs(condition_code: ConditionCode) -> ByteInstructionInputs:
    return ByteInstructionInputs(inputs=[
        ConditionalInputs(status_register=status_register,
                          condition_code=condition_code)
        for status_register, condition_code in itertools.product(
            ALL_CONDITION_CODE_REGISTERS,
            [condition_code])
    ])


def __create_bcc_word_inputs(condition_code: ConditionCode) -> WordInstructionInputs:
    return WordInstructionInputs(inputs=[
        ConditionalInputs(status_register=status_register,
                          condition_code=condition_code)
        for status_register, condition_code in itertools.product(
            ALL_CONDITION_CODE_REGISTERS,
            [condition_code])
    ])


DBT_WORD_INPUTS = __create_dbcc_word_inputs(ConditionCode.T)
DBF_WORD_INPUTS = __create_dbcc_word_inputs(ConditionCode.F)
DBHI_WORD_INPUTS = __create_dbcc_word_inputs(ConditionCode.HI)
DBLS_WORD_INPUTS = __create_dbcc_word_inputs(ConditionCode.LS)
DBCC_WORD_INPUTS = __create_dbcc_word_inputs(ConditionCode.CC)
DBCS_WORD_INPUTS = __create_dbcc_word_inputs(ConditionCode.CS)
DBNE_WORD_INPUTS = __create_dbcc_word_inputs(ConditionCode.NE)
DBEQ_WORD_INPUTS = __create_dbcc_word_inputs(ConditionCode.EQ)
DBVC_WORD_INPUTS = __create_dbcc_word_inputs(ConditionCode.VC)
DBVS_WORD_INPUTS = __create_dbcc_word_inputs(ConditionCode.VS)
DBPL_WORD_INPUTS = __create_dbcc_word_inputs(ConditionCode.PL)
DBMI_WORD_INPUTS = __create_dbcc_word_inputs(ConditionCode.MI)
DBGE_WORD_INPUTS = __create_dbcc_word_inputs(ConditionCode.GE)
DBLT_WORD_INPUTS = __create_dbcc_word_inputs(ConditionCode.LT)
DBGT_WORD_INPUTS = __create_dbcc_word_inputs(ConditionCode.GT)
DBLE_WORD_INPUTS = __create_dbcc_word_inputs(ConditionCode.LE)

BRA_BYTE_INPUTS = __create_bcc_byte_inputs(ConditionCode.T)
BHI_BYTE_INPUTS = __create_bcc_byte_inputs(ConditionCode.HI)
BLS_BYTE_INPUTS = __create_bcc_byte_inputs(ConditionCode.LS)
BCC_BYTE_INPUTS = __create_bcc_byte_inputs(ConditionCode.CC)
BCS_BYTE_INPUTS = __create_bcc_byte_inputs(ConditionCode.CS)
BNE_BYTE_INPUTS = __create_bcc_byte_inputs(ConditionCode.NE)
BEQ_BYTE_INPUTS = __create_bcc_byte_inputs(ConditionCode.EQ)
BVC_BYTE_INPUTS = __create_bcc_byte_inputs(ConditionCode.VC)
BVS_BYTE_INPUTS = __create_bcc_byte_inputs(ConditionCode.VS)
BPL_BYTE_INPUTS = __create_bcc_byte_inputs(ConditionCode.PL)
BMI_BYTE_INPUTS = __create_bcc_byte_inputs(ConditionCode.MI)
BGE_BYTE_INPUTS = __create_bcc_byte_inputs(ConditionCode.GE)
BLT_BYTE_INPUTS = __create_bcc_byte_inputs(ConditionCode.LT)
BGT_BYTE_INPUTS = __create_bcc_byte_inputs(ConditionCode.GT)
BLE_BYTE_INPUTS = __create_bcc_byte_inputs(ConditionCode.LE)

BRA_WORD_INPUTS = __create_bcc_word_inputs(ConditionCode.T)
BHI_WORD_INPUTS = __create_bcc_word_inputs(ConditionCode.HI)
BLS_WORD_INPUTS = __create_bcc_word_inputs(ConditionCode.LS)
BCC_WORD_INPUTS = __create_bcc_word_inputs(ConditionCode.CC)
BCS_WORD_INPUTS = __create_bcc_word_inputs(ConditionCode.CS)
BNE_WORD_INPUTS = __create_bcc_word_inputs(ConditionCode.NE)
BEQ_WORD_INPUTS = __create_bcc_word_inputs(ConditionCode.EQ)
BVC_WORD_INPUTS = __create_bcc_word_inputs(ConditionCode.VC)
BVS_WORD_INPUTS = __create_bcc_word_inputs(ConditionCode.VS)
BPL_WORD_INPUTS = __create_bcc_word_inputs(ConditionCode.PL)
BMI_WORD_INPUTS = __create_bcc_word_inputs(ConditionCode.MI)
BGE_WORD_INPUTS = __create_bcc_word_inputs(ConditionCode.GE)
BLT_WORD_INPUTS = __create_bcc_word_inputs(ConditionCode.LT)
BGT_WORD_INPUTS = __create_bcc_word_inputs(ConditionCode.GT)
BLE_WORD_INPUTS = __create_bcc_word_inputs(ConditionCode.LE)

BSR_BYTE_INPUTS = __create_bcc_byte_inputs(ConditionCode.T)
BSR_WORD_INPUTS = __create_bcc_word_inputs(ConditionCode.T)
