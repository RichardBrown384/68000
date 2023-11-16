"""
This module contains a representation of the M68000's status register
"""

import dataclasses

from .condition_code import ConditionCode

_FLAG_T = 0x8000
_FLAG_S = 0x2000
_FLAG_X = 0x0010
_FLAG_N = 0x0008
_FLAG_Z = 0x0004
_FLAG_V = 0x0002
_FLAG_C = 0x0001


# pylint: disable=too-many-instance-attributes, invalid-name
@dataclasses.dataclass(kw_only=True)
class StatusRegister:
    """Representation of the M68000's status and condition code register."""
    t: bool = False
    s: bool = True
    interrupt_mask: int = 0
    x: bool = False
    n: bool = False
    z: bool = False
    v: bool = False
    c: bool = False

    # pylint: disable=too-many-return-statements, invalid-name
    def test(self, condition: ConditionCode) -> bool:
        """Returns true if the status register matches the given condition code."""
        n = self.n
        z = self.z
        v = self.v
        c = self.c
        match condition:
            case ConditionCode.T:
                return True
            case ConditionCode.F:
                return False
            case ConditionCode.HI:
                return not (c or z)
            case ConditionCode.LS:
                return c or z
            case ConditionCode.CC:
                return not c
            case ConditionCode.CS:
                return c
            case ConditionCode.NE:
                return not z
            case ConditionCode.EQ:
                return z
            case ConditionCode.VC:
                return not v
            case ConditionCode.VS:
                return v
            case ConditionCode.PL:
                return not n
            case ConditionCode.MI:
                return n
            case ConditionCode.GE:
                return not n ^ v
            case ConditionCode.LT:
                return n ^ v
            case ConditionCode.GT:
                return not (z or (n ^ v))
            case ConditionCode.LE:
                return z or (n ^ v)
            case _:
                return False

    def as_int(self) -> int:
        result = 0

        def accumulate(flag, bits):
            nonlocal result
            if flag:
                result |= bits

        accumulate(self.t, _FLAG_T)
        accumulate(self.s, _FLAG_S)
        result |= (self.interrupt_mask & 7) << 8
        accumulate(self.x, _FLAG_X)
        accumulate(self.n, _FLAG_N)
        accumulate(self.z, _FLAG_Z)
        accumulate(self.v, _FLAG_V)
        accumulate(self.c, _FLAG_C)
        return result

    @classmethod
    def from_int(cls, v: int):
        return StatusRegister(
            t=(v & _FLAG_T) != 0,
            s=(v & _FLAG_S) != 0,
            interrupt_mask=(v >> 8) & 7,
            x=(v & _FLAG_X) != 0,
            n=(v & _FLAG_N) != 0,
            z=(v & _FLAG_Z) != 0,
            v=(v & _FLAG_V) != 0,
            c=(v & _FLAG_C) != 0)

    @classmethod
    def combine(cls, supervisor, condition):
        return StatusRegister(
            t=supervisor.t,
            s=supervisor.s,
            interrupt_mask=supervisor.interrupt_mask,
            x=condition.x,
            n=condition.n,
            z=condition.z,
            v=condition.v,
            c=condition.c
        )
