import dataclasses


@dataclasses.dataclass(kw_only=True)
class ConditionalBranch:
    """Class to indicate if the test case should branch or not."""
    branch: bool = False
    displacement: int = 0
