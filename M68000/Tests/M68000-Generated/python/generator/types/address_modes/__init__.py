import dataclasses

from .address_decrement import AddressDecrement
from .address_displacement import AddressDisplacement
from .address_increment import AddressIncrement
from .address_index import AddressIndex
from .address_indirect import AddressIndirect
from .address_register import AddressRegister
from .bitwise_immediate import BitwiseImmediate
from .branch_byte import BranchByte
from .branch_subroutine_byte import BranchSubroutineByte
from .branch_subroutine_word import BranchSubroutineWord
from .branch_word import BranchWord
from .condition_code_register import ConditionCodeRegisterMode
from .decrement_and_branch import DecrementAndBranch
from .data_direct import DataRegister
from .immediate import Immediate
from .index_register import IndexRegisterType, IndexRegisterSize, IndexRegister
from .long import Long
from .null import Null
from .pc_displacement import PcDisplacement
from .pc_index import PcIndex
from .quick_immediate import QuickImmediate
from .short import Short
from .stack_decrement import StackDecrement
from .stack_increment import StackIncrement
from .status_register import StatusRegisterMode

AddressMode = Null | \
              DataRegister | \
              AddressRegister | \
              AddressIndirect | \
              AddressIncrement | \
              StackIncrement | \
              AddressDecrement | \
              StackDecrement | \
              AddressDisplacement | \
              AddressIndex | \
              Short | \
              Long | \
              PcDisplacement | \
              PcIndex | \
              Immediate | \
              BitwiseImmediate | \
              QuickImmediate | \
              DecrementAndBranch | \
              BranchByte | \
              BranchWord | \
              BranchSubroutineByte | \
              BranchSubroutineWord | \
              StatusRegisterMode | \
              ConditionCodeRegisterMode


@dataclasses.dataclass(kw_only=True)
class AddressModes:
    program_counter: int
    source: AddressMode = None
    destination: AddressMode = None
