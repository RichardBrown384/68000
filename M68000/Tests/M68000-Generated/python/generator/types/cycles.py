from typing import Callable

from .instruction_inputs import InstructionInputs

CycleCountCalculator = Callable[[int, int, InstructionInputs], int]


def takes_n_cycles(n: int):
    def func(*_):
        return n

    return func


def takes_n_cycles_plus_source(n: int):
    def func(source, *_):
        return n + source

    return func


def takes_n_cycles_plus_destination(n: int):
    def func(_source, destination, *_):
        return n + destination

    return func
