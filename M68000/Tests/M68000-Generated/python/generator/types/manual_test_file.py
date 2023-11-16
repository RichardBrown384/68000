import dataclasses
from typing import List

from .test_data import TestData


@dataclasses.dataclass(kw_only=True)
class ManualTestFile:
    name: str
    d: List[TestData]

    def data(self):
        return self.d
