import importlib
import pkgutil
from inspect import getmembers

import orjson

from generator import test_files
from generator import test_files_manual
from generator.types.manual_test_file import \
    ManualTestFile
from generator.types.sized_instruction_test_file import \
    SizedInstructionTestFile


def is_test_file(obj: object) -> bool:
    return isinstance(obj, SizedInstructionTestFile | ManualTestFile)


def find_test_files_in_module(root_module: object):
    for _, name, _ in pkgutil.walk_packages(root_module.__path__):
        imported_module = importlib.import_module(f'.{name}', package=root_module.__name__)
        for _, test_file in getmembers(imported_module, is_test_file):
            yield test_file


def write_test_data_to_json_file(test_data_file: SizedInstructionTestFile) -> None:
    with open(f'{test_data_file.name}.json', 'wb') as file:
        # pylint: disable=no-member
        file.write(orjson.dumps(
            test_data_file.data(), option=orjson.OPT_NON_STR_KEYS
        ))


def write_test_data_file_in_module(module):
    for test_file in find_test_files_in_module(module):
        write_test_data_to_json_file(test_file)


def main():
    write_test_data_file_in_module(test_files)
    write_test_data_file_in_module(test_files_manual)


if __name__ == '__main__':
    main()
