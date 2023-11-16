"""
This module contains a representation of the quick immediate address mode
"""
from .default_address_mode_base import DefaultAddressModeBase
from ..size import SizeAdapter


class QuickImmediate(DefaultAddressModeBase):
    def assembly(self, _: SizeAdapter, data: int):
        return f'#{data}'
