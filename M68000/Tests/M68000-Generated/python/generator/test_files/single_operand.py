"""
This module contains test file descriptions for the
single operand instructions.
"""

from typing import List

from ..address_mode_data.single_operand import \
    SINGLE_TO_DATA_REGISTER, \
    SINGLE_TO_MEMORY
from ..inputs.single_operand import \
    NEGX_BYTE_INPUTS, NEGX_WORD_INPUTS, NEGX_LONG_INPUTS, \
    CLR_BYTE_INPUTS, CLR_WORD_INPUTS, CLR_LONG_INPUTS, \
    NEG_BYTE_INPUTS, NEG_WORD_INPUTS, NEG_LONG_INPUTS, \
    NOT_BYTE_INPUTS, NOT_WORD_INPUTS, NOT_LONG_INPUTS, \
    NBCD_BYTE_INPUTS, \
    TAS_BYTE_INPUTS, \
    TST_BYTE_INPUTS, TST_WORD_INPUTS, TST_LONG_INPUTS, \
    ST_INPUTS, SF_INPUTS, \
    SHI_INPUTS, SLS_INPUTS, \
    SCC_INPUTS, SCS_INPUTS, \
    SNE_INPUTS, SEQ_INPUTS, \
    SVC_INPUTS, SVS_INPUTS, \
    SPL_INPUTS, SMI_INPUTS, \
    SGE_INPUTS, SLT_INPUTS, \
    SGT_INPUTS, SLE_INPUTS

from ..outputs.single_operand import \
    produce_negx_outputs, produce_clr_outputs, produce_neg_outputs, \
    produce_not_outputs, produce_nbcd_outputs, produce_tst_outputs, \
    produce_scc_outputs, produce_tas_outputs
from ..types.cycles import takes_n_cycles, takes_n_cycles_plus_destination
from ..types.sized_instruction_inputs import ByteInstructionInputs
from ..types.sized_instruction_test_file import SizedInstructionTestFile, ModesAndCycles


def __modes_and_cycles(
        register_to_register: int,
        memory_to_memory: int) -> List[ModesAndCycles]:
    return [
        ModesAndCycles(address_modes=[
            SINGLE_TO_DATA_REGISTER
        ], cycles=takes_n_cycles(register_to_register)),
        ModesAndCycles(address_modes=[
            SINGLE_TO_MEMORY
        ], cycles=takes_n_cycles_plus_destination(memory_to_memory))
    ]


def __scc_modes_and_cycles(
        register_to_register_false: int,
        register_to_register_true: int,
        memory_to_memory: int) -> List[ModesAndCycles]:

    def register_cycles(_source, _destination, inputs):
        if inputs.test:
            return register_to_register_true
        return register_to_register_false

    return [
        ModesAndCycles(address_modes=[
            SINGLE_TO_DATA_REGISTER
        ], cycles=register_cycles),
        ModesAndCycles(address_modes=[
            SINGLE_TO_MEMORY
        ], cycles=takes_n_cycles_plus_destination(memory_to_memory))
    ]


def __create_scc_test_file(
        instruction: str,
        inputs: ByteInstructionInputs) -> SizedInstructionTestFile:
    return SizedInstructionTestFile(
        instruction=instruction,
        name=f'{instruction.lower()}_byte',
        inputs=inputs,
        outputs_producer=produce_scc_outputs,
        modes=__scc_modes_and_cycles(
            register_to_register_false=4,
            register_to_register_true=6,
            memory_to_memory=8)
    )


NEGX_BYTE = SizedInstructionTestFile(
    instruction='NEGX.B',
    name='negx_byte',
    inputs=NEGX_BYTE_INPUTS,
    outputs_producer=produce_negx_outputs,
    modes=__modes_and_cycles(register_to_register=4, memory_to_memory=8)
)

NEGX_WORD = SizedInstructionTestFile(
    instruction='NEGX.W',
    name='negx_word',
    inputs=NEGX_WORD_INPUTS,
    outputs_producer=produce_negx_outputs,
    modes=__modes_and_cycles(register_to_register=4, memory_to_memory=8)
)

NEGX_LONG = SizedInstructionTestFile(
    instruction='NEGX.L',
    name='negx_long',
    inputs=NEGX_LONG_INPUTS,
    outputs_producer=produce_negx_outputs,
    modes=__modes_and_cycles(register_to_register=6, memory_to_memory=12)
)

CLR_BYTE = SizedInstructionTestFile(
    instruction='CLR.B',
    name='clr_byte',
    inputs=CLR_BYTE_INPUTS,
    outputs_producer=produce_clr_outputs,
    modes=__modes_and_cycles(register_to_register=4, memory_to_memory=8)
)

CLR_WORD = SizedInstructionTestFile(
    instruction='CLR.W',
    name='clr_word',
    inputs=CLR_WORD_INPUTS,
    outputs_producer=produce_clr_outputs,
    modes=__modes_and_cycles(register_to_register=4, memory_to_memory=8)
)

CLR_LONG = SizedInstructionTestFile(
    instruction='CLR.L',
    name='clr_long',
    inputs=CLR_LONG_INPUTS,
    outputs_producer=produce_clr_outputs,
    modes=__modes_and_cycles(register_to_register=6, memory_to_memory=12)
)

NEG_BYTE = SizedInstructionTestFile(
    instruction='NEG.B',
    name='neg_byte',
    inputs=NEG_BYTE_INPUTS,
    outputs_producer=produce_neg_outputs,
    modes=__modes_and_cycles(register_to_register=4, memory_to_memory=8)
)

NEG_WORD = SizedInstructionTestFile(
    instruction='NEG.W',
    name='neg_word',
    inputs=NEG_WORD_INPUTS,
    outputs_producer=produce_neg_outputs,
    modes=__modes_and_cycles(register_to_register=4, memory_to_memory=8)
)

NEG_LONG = SizedInstructionTestFile(
    instruction='NEG.L',
    name='neg_long',
    inputs=NEG_LONG_INPUTS,
    outputs_producer=produce_neg_outputs,
    modes=__modes_and_cycles(register_to_register=6, memory_to_memory=12)
)

NOT_BYTE = SizedInstructionTestFile(
    instruction='NOT.B',
    name='not_byte',
    inputs=NOT_BYTE_INPUTS,
    outputs_producer=produce_not_outputs,
    modes=__modes_and_cycles(register_to_register=4, memory_to_memory=8)
)

NOT_WORD = SizedInstructionTestFile(
    instruction='NOT.W',
    name='not_word',
    inputs=NOT_WORD_INPUTS,
    outputs_producer=produce_not_outputs,
    modes=__modes_and_cycles(register_to_register=4, memory_to_memory=8)
)

NOT_LONG = SizedInstructionTestFile(
    instruction='NOT.L',
    name='not_long',
    inputs=NOT_LONG_INPUTS,
    outputs_producer=produce_not_outputs,
    modes=__modes_and_cycles(register_to_register=6, memory_to_memory=12)
)

NBCD_BYTE = SizedInstructionTestFile(
    instruction='NBCD',
    name='nbcd_byte',
    inputs=NBCD_BYTE_INPUTS,
    outputs_producer=produce_nbcd_outputs,
    modes=__modes_and_cycles(register_to_register=6, memory_to_memory=8)
)

TAS_BYTE = SizedInstructionTestFile(
    instruction='TAS',
    name='tas',
    inputs=TAS_BYTE_INPUTS,
    outputs_producer=produce_tas_outputs,
    modes=__modes_and_cycles(register_to_register=4, memory_to_memory=10)
)

TST_BYTE = SizedInstructionTestFile(
    instruction='TST.B',
    name='tst_byte',
    inputs=TST_BYTE_INPUTS,
    outputs_producer=produce_tst_outputs,
    modes=__modes_and_cycles(register_to_register=4, memory_to_memory=4)
)

TST_WORD = SizedInstructionTestFile(
    instruction='TST.W',
    name='tst_word',
    inputs=TST_WORD_INPUTS,
    outputs_producer=produce_tst_outputs,
    modes=__modes_and_cycles(register_to_register=4, memory_to_memory=4)
)

TST_LONG = SizedInstructionTestFile(
    instruction='TST.L',
    name='tst_long',
    inputs=TST_LONG_INPUTS,
    outputs_producer=produce_tst_outputs,
    modes=__modes_and_cycles(register_to_register=4, memory_to_memory=4)
)

ST_BYTE = __create_scc_test_file('ST', ST_INPUTS)
SF_BYTE = __create_scc_test_file('SF', SF_INPUTS)
SHI_BYTE = __create_scc_test_file('SHI', SHI_INPUTS)
SLS_BYTE = __create_scc_test_file('SLS', SLS_INPUTS)
SCC_BYTE = __create_scc_test_file('SCC', SCC_INPUTS)
SCS_BYTE = __create_scc_test_file('SCS', SCS_INPUTS)
SNE_BYTE = __create_scc_test_file('SNE', SNE_INPUTS)
SEQ_BYTE = __create_scc_test_file('SEQ', SEQ_INPUTS)
SVC_BYTE = __create_scc_test_file('SVC', SVC_INPUTS)
SVS_BYTE = __create_scc_test_file('SVS', SVS_INPUTS)
SPL_BYTE = __create_scc_test_file('SPL', SPL_INPUTS)
SMI_BYTE = __create_scc_test_file('SMI', SMI_INPUTS)
SGE_BYTE = __create_scc_test_file('SGE', SGE_INPUTS)
SLT_BYTE = __create_scc_test_file('SLT', SLT_INPUTS)
SGT_BYTE = __create_scc_test_file('SGT', SGT_INPUTS)
SLE_BYTE = __create_scc_test_file('SLE', SLE_INPUTS)
