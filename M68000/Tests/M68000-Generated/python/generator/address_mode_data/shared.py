import itertools
from typing import List

from ..types.address_modes import AddressModes, IndexRegisterType


def produce_address_mode_products(
        pcs, sources, destinations, predicate=None) -> List[AddressModes]:
    """Produces the cross product of address modes and optionally filters."""
    return [
        AddressModes(program_counter=pc, source=source, destination=destination)
        for pc, source, destination in itertools.product(pcs, sources, destinations)
        if not predicate or predicate(source, destination)
    ]


def source_register_is_not_destination_register(source, destination):
    """Excludes the OP Dn, Dn and OP An, An cases."""
    return source.number != destination.number


def source_index_data_register_is_not_destination_data_register(source, destination):
    """Excludes the OP (d, An, Dm), Dm case."""
    return source.index.type == IndexRegisterType.ADDRESS_REGISTER or \
           source.index.number != destination.number


def source_index_address_register_is_not_destination_address_register(source, destination):
    """Excludes the OP (d, An, Am), Am case."""
    return source.index.type != IndexRegisterType.ADDRESS_REGISTER or \
           source.index.number != destination.number


def source_or_index_register_is_not_destination_address_register(source, destination):
    return source_register_is_not_destination_register(source, destination) and \
           source_index_address_register_is_not_destination_address_register(source, destination)


def destination_index_data_register_is_not_source_data_register(source, destination):
    """Excludes the OP Dm, (d, An, Dm) case."""
    return destination.index.type == IndexRegisterType.ADDRESS_REGISTER or \
           destination.index.number != source.number


def produce_address_mode_products_excluding_same(pcs, sources, destinations) -> List[AddressModes]:
    return produce_address_mode_products(
        pcs, sources, destinations,
        predicate=source_register_is_not_destination_register
    )
