from .default_address_mode_base import DefaultAddressModeBase
from ..instruction_inputs import InstructionInputs
from ..size import SizeAdapter


class BitwiseImmediate(DefaultAddressModeBase):

    def assembly(self, size_adapter: SizeAdapter, data: int) -> str:
        return f'#{data & 0xFF}'

    def extension_words(self, size_adapter: SizeAdapter) -> int:
        return 1

    def cycles(self, size_adapter: SizeAdapter, inputs: InstructionInputs) -> int:
        return 4
