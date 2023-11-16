from .default_address_mode_base import DefaultAddressModeBase
from ..size import SizeAdapter


class Null(DefaultAddressModeBase):

    def assembly(self, size_adapter: SizeAdapter, data: int) -> str:
        return ''
