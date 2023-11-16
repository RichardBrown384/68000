"""
This module defines the status register mode
"""

from .default_address_mode_base import DefaultAddressModeBase
from ..size import SizeAdapter


class StatusRegisterMode(DefaultAddressModeBase):
    """This class defines the status register address mode."""
    def assembly(self, size_adapter: SizeAdapter, data: int) -> str:
        return 'SR'
