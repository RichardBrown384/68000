import dataclasses
import itertools
from typing import Callable, List, Iterable

from .address_modes import AddressModes
from .cycles import CycleCountCalculator
from .instruction_inputs import \
    InstructionInputs
from .instruction_outputs import InstructionOutputs

from .size import \
    SizeCharacteristics
from .sized_instruction_inputs import SizedInstructionInputs
from .test_data import TestData, GivenConditions, ThenConditions

InstructionOutputsProducer = Callable[
    [SizeCharacteristics, InstructionInputs],
    InstructionOutputs
]


@dataclasses.dataclass(kw_only=True)
class ModesAndCycles:
    """List of a list of address modes and how to compute their cycle times."""
    address_modes: List[List[AddressModes]]
    cycles: CycleCountCalculator


@dataclasses.dataclass(kw_only=True)
class SizedInstructionTestFile:
    instruction: str
    name: str
    inputs: SizedInstructionInputs
    outputs_producer: InstructionOutputsProducer
    modes: List[ModesAndCycles]
    outputs: List[InstructionOutputs] = dataclasses.field(init=False)

    def __post_init__(self):
        self.outputs = [
            self.outputs_producer(self.inputs.characteristics, instruction_input)
            for instruction_input in self.inputs.inputs
        ]

    @staticmethod
    def __produce_operand_assembly(source: str, destination: str) -> str:
        if source and destination:
            return f' {source}, {destination}'
        if source or destination:
            return f' {source or destination}'
        return ''

    def _produce_assembly(self, mode_data: AddressModes, inputs: InstructionInputs) -> str:
        source, destination = \
            mode_data.source, mode_data.destination

        adapter = self.inputs.adapter

        source_assembly = source.assembly(adapter, inputs.src)
        destination_assembly = destination.assembly(adapter, inputs.dst)
        operand_assembly = self.__produce_operand_assembly(
            source_assembly, destination_assembly)

        return f'{self.instruction}{operand_assembly}'

    def _produce_given_conditions(self,
                                  modes: AddressModes,
                                  inputs: InstructionInputs) -> GivenConditions:

        program_counter, source, destination = \
            modes.program_counter, modes.source, modes.destination

        adapter = self.inputs.adapter

        source_inputs = source.produce_inputs(adapter, program_counter, inputs.src)
        destination_inputs = destination.produce_inputs(adapter, program_counter, inputs.dst)

        is_supervisor = inputs.status_register.s

        address_registers = \
            {7: inputs.ssp if is_supervisor else inputs.usp} | \
            source_inputs.a | \
            destination_inputs.a
        sp = address_registers[7]
        usp = inputs.usp if is_supervisor else sp
        ssp = inputs.ssp if not is_supervisor else sp

        return GivenConditions(
            status_register=inputs.status_register,
            pc=program_counter,
            d=source_inputs.d | destination_inputs.d,
            a=address_registers,
            memory=source_inputs.memory | destination_inputs.memory,
            usp=usp,
            ssp=ssp
        )

    def _produce_then_conditions(
            self,
            given: GivenConditions,
            mode_data: AddressModes,
            inputs: InstructionInputs,
            outputs: InstructionOutputs,
            cycle_calculator: CycleCountCalculator) -> ThenConditions:

        program_counter, source, destination = \
            mode_data.program_counter, mode_data.source, mode_data.destination

        adapter = self.inputs.adapter

        source_outputs = source.produce_outputs(adapter, program_counter, inputs.src)
        destination_outputs = destination.produce_outputs(adapter, program_counter, outputs.dst)

        sp = given.a[7]
        usp = given.usp
        ssp = given.ssp

        output_address_registers = \
            {7: sp} | \
            source_outputs.a | \
            destination_outputs.a

        if outputs.status_register.s ^ inputs.status_register.s:
            if outputs.status_register.s:
                usp = output_address_registers[7]
                output_address_registers[7] = ssp
            else:
                ssp = output_address_registers[7]
                output_address_registers[7] = usp

        extension_words = \
            source.extension_words(adapter) + \
            destination.extension_words(adapter)

        branch = destination.conditional_branch(inputs)
        displacement = branch.displacement if branch.branch else 2 * extension_words

        return ThenConditions(
            status_register=outputs.status_register,
            pc=program_counter + 2 + displacement,
            cycles=cycle_calculator(
                source.cycles(adapter, inputs),
                destination.cycles(adapter, inputs),
                inputs
            ),
            d=source_outputs.d | destination_outputs.d,
            a=output_address_registers,
            memory=source_outputs.memory | destination_outputs.memory,
            usp=usp,
            ssp=ssp,
            stopped=inputs.stopped
        )

    def data(self) -> List[TestData]:
        def generator() -> Iterable[TestData]:
            for mode in self.modes:
                for modes, input_output in itertools.product(
                        itertools.chain(*mode.address_modes),
                        zip(self.inputs.inputs, self.outputs)):
                    inputs, outputs = input_output
                    given = self._produce_given_conditions(modes, inputs)
                    assembly = self._produce_assembly(modes, inputs)
                    then = self._produce_then_conditions(given, modes, inputs, outputs, mode.cycles)
                    yield TestData(
                        given=given,
                        when=[assembly],
                        then=then)

        return list(generator())
