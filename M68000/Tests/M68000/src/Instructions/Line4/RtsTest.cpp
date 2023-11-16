#include "M68000/Fixtures/M68000Test.h"

class RTSTest : public M68000Test {};

TEST_F(RTSTest, RtsWorks) {
    Given({
        "A7 is 0x00FFFFFC",
        "(0x00FFFFFC).L is 0x00DDEE02",
        "SR is S,0,0"
    });
    When({
        "RTS"
    });
    Then({
        "A7 is 0x01000000",
        "(0x00FFFFFC).L is 0x00DDEE02",
        "PC is 0x00DDEE02",
        "SR is S,0,0",
        "CYCLES is 16"
    });
}
