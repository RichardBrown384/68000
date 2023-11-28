#include "M68000/Fixtures/M68000Test.h"

class RTRTest : public M68000Test {};

TEST_F(RTRTest, RtrWorks) {
    Given({
        "SR is S,0,0",
        "PC is 0x1000",
        "A7 is 0x00FFFFFA",
        "(0x00FFFFFA).W is 0x0011",
        "(0x00FFFFFC).L is 0x00CAFE00",
    });
    When({
        "RTR"
    });
    Then({
        "SR is S,0,XC",
        "PC is 0x00CAFE00",
        "CYCLES is 20",
        "A7 is 0x01000000",
        "(0x00FFFFFA).W is 0x0011",
        "(0x00FFFFFC).L is 0x00CAFE00",
    });
}
