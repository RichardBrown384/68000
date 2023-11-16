"""
This module defines the condition code register
"""

from .default_address_mode_base import DefaultAddressModeBase
from ..size import SizeAdapter


class ConditionCodeRegisterMode(DefaultAddressModeBase):
    """This class defines the status register address mode."""
    def assembly(self, size_adapter: SizeAdapter, data: int) -> str:
        return 'CCR'
