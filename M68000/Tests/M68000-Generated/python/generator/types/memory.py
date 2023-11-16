from functools import reduce


def __mask_address(address):
    return address & 0x00FF_FFFF


def create_memory_byte(address, value):
    return {
        __mask_address(address): value & 0xFF
    }


def create_memory_word(address, value):
    return {
        __mask_address(address): (value >> 8) & 0xFF,
        __mask_address(address + 1): value & 0xFF
    }


def create_memory_long(address, value):
    return {
        __mask_address(address): (value >> 24) & 0xFF,
        __mask_address(address + 1): (value >> 16) & 0xFF,
        __mask_address(address + 2): (value >> 8) & 0xFF,
        __mask_address(address + 3): value & 0xFF
    }


def __merge_memory(a, b):
    return {**a, **b}


def create_memory_words(address, *args):
    return reduce(__merge_memory, (
        create_memory_word(address + 2 * i, arg) for i, arg in enumerate(args)
    ))


def create_memory_longs(address, *args):
    return reduce(__merge_memory, (
        create_memory_long(address + 4 * i, arg) for i, arg in enumerate(args)
    ))


def create_stack_frame(address, status, program_counter):
    return __merge_memory(
        create_memory_word(address, status),
        create_memory_long(address + 2, program_counter)
    )
