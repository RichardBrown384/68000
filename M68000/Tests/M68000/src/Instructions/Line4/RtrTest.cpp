#include "M68000/Fixtures/M68000Test.h"

class RTRTest : public M68000Test {};

TEST_F(RTRTest, RtrWorks) {
    Given({
        "A7 is 0x00FFFFFA",
        "(0x00FFFFFA).W is 0x0011",
        "(0x00FFFFFC).L is 0x00CAFE00",
        "SR is S,0,0"
    });
    When({
        "RTR"
    });
    Then({
        "A7 is 0x01000000",
        "(0x00FFFFFA).W is 0x0011",
        "(0x00FFFFFC).L is 0x00CAFE00",
        "PC is 0x00CAFE00",
        "SR is S,0,XC",
        "CYCLES is 20"
    });
}
