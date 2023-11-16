"""
This module defines the branch word address mode
"""
import dataclasses

from .conditional_branch import ConditionalBranch
from .default_address_mode_base import DefaultAddressModeBase
from .util.checks import check_displacement_word
from ..instruction_inputs import InstructionInputs
from ..size import SizeAdapter

_CYCLES_CONDITION_FALSE = 12
_CYCLES_CONDITION_TRUE = 10


@dataclasses.dataclass(kw_only=True)
class BranchWord(DefaultAddressModeBase):
    """The class for branch word."""
    displacement: int

    def __post_init__(self):
        assert check_displacement_word(self.displacement)
        self.__assembly = f'*{self.displacement:+}'

    def assembly(self, size_adapter: SizeAdapter, data: int) -> str:
        return self.__assembly

    def extension_words(self, size_adapter: SizeAdapter) -> int:
        return 1

    def conditional_branch(self, inputs: InstructionInputs) -> ConditionalBranch:
        return ConditionalBranch(
            branch=inputs.test,
            displacement=self.displacement - 2)

    def cycles(self, size_adapter: SizeAdapter, inputs: InstructionInputs) -> int:
        return _CYCLES_CONDITION_TRUE if inputs.test else _CYCLES_CONDITION_FALSE
