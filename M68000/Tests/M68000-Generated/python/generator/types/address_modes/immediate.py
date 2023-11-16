from .default_address_mode_base import DefaultAddressModeBase
from ..instruction_inputs import InstructionInputs
from ...types.size import SizeAdapter


class Immediate(DefaultAddressModeBase):

    def assembly(self, size_adapter: SizeAdapter, data: int):
        return f'#{data & size_adapter.immediate_operand_mask}'

    def extension_words(self, size_adapter: SizeAdapter) -> int:
        return size_adapter.operand_words

    def cycles(self, size_adapter: SizeAdapter, inputs: InstructionInputs) -> int:
        return 4 * size_adapter.operand_words
