#include "M68000/Fixtures/M68000Test.h"

class MovemRegisterTestWord : public M68000Test {};

TEST_F(MovemRegisterTestWord, AddressIndirect) {
    Given({
        "D1 is 0x0000",
        "D2 is 0x0000",
        "A4 is 0x2000",
        "A5 is 0x0000",
        "SR is S,0,0",
        "(0x2000).W is 0xDEAD",
        "(0x2002).W is 0xBEEF",
        "(0x2004).W is 0xCAFE",
        "(0x2006).W is 0xBEAD"
    });
    When({
        "MOVEM.W (A4), D1-D2/A4-A5"
    });
    Then({
        "D1 is 0xFFFFDEAD",
        "D2 is 0xFFFFBEEF",
        "A4 is 0xFFFFCAFE",
        "A5 is 0xFFFFBEAD",
        "SR is S,0,0",
        "(0x2000).W is 0xDEAD",
        "(0x2002).W is 0xBEEF",
        "(0x2004).W is 0xCAFE",
        "(0x2006).W is 0xBEAD",
        "CYCLES is 28"
    });
}

TEST_F(MovemRegisterTestWord, AddressIncrement) {
    Given({
        "D1 is 0x0000",
        "D2 is 0x0000",
        "A4 is 0x2000",
        "A5 is 0x0000",
        "SR is S,0,0",
        "(0x2000).W is 0xDEAD",
        "(0x2002).W is 0xBEEF",
        "(0x2004).W is 0xCAFE",
        "(0x2006).W is 0xBEAD"
    });
    When({
        "MOVEM.W (A4)+, D1-D2/A4-A5"
    });
    Then({
        "D1 is 0xFFFFDEAD",
        "D2 is 0xFFFFBEEF",
        "A4 is 0x00002008",
        "A5 is 0xFFFFBEAD",
        "SR is S,0,0",
        "(0x2000).W is 0xDEAD",
        "(0x2002).W is 0xBEEF",
        "(0x2004).W is 0xCAFE",
        "(0x2006).W is 0xBEAD",
        "CYCLES is 28"
    });
}

TEST_F(MovemRegisterTestWord, AddressDisplacement) {
    Given({
        "D1 is 0x0000",
        "D2 is 0x0000",
        "A4 is 0x2000",
        "A5 is 0x0000",
        "SR is S,0,0",
        "(0x2200).W is 0xDEAD",
        "(0x2202).W is 0xBEEF",
        "(0x2204).W is 0xCAFE",
        "(0x2206).W is 0x7EAD"
    });
    When({
        "MOVEM.W (0x0200, A4), D1-D2/A4-A5"
    });
    Then({
        "D1 is 0xFFFFDEAD",
        "D2 is 0xFFFFBEEF",
        "A4 is 0xFFFFCAFE",
        "A5 is 0x00007EAD",
        "SR is S,0,0",
        "(0x2200).W is 0xDEAD",
        "(0x2202).W is 0xBEEF",
        "(0x2204).W is 0xCAFE",
        "(0x2206).W is 0x7EAD",
        "CYCLES is 32"
    });
}


TEST_F(MovemRegisterTestWord, AddressIndex) {
    Given({
        "D1 is 0x0000",
        "D2 is 0x0000",
        "A4 is 0x2000",
        "A5 is 0x0000",
        "A6 is 0x01FE",
        "SR is S,0,0",
        "(0x2200).W is 0xDEAD",
        "(0x2202).W is 0xBEEF",
        "(0x2204).W is 0xCAFE",
        "(0x2206).W is 0x7EAD"
    });
    When({
        "MOVEM.W (0x02, A4, A6.L), D1-D2/A4-A5"
    });
    Then({
        "D1 is 0xFFFFDEAD",
        "D2 is 0xFFFFBEEF",
        "A4 is 0xFFFFCAFE",
        "A5 is 0x00007EAD",
        "A6 is 0x000001FE",
        "SR is S,0,0",
        "(0x2200).W is 0xDEAD",
        "(0x2202).W is 0xBEEF",
        "(0x2204).W is 0xCAFE",
        "(0x2206).W is 0x7EAD",
        "CYCLES is 34"
    });
}

TEST_F(MovemRegisterTestWord, Short) {
    Given({
        "D1 is 0x0000",
        "D2 is 0x0000",
        "A4 is 0x2000",
        "A5 is 0x0000",
        "SR is S,0,0",
        "(0x2200).W is 0xDEAD",
        "(0x2202).W is 0xBEEF",
        "(0x2204).W is 0xCAFE",
        "(0x2206).W is 0x7EAD"
    });
    When({
        "MOVEM.W (0x2200).W, D1-D2/A4-A5"
    });
    Then({
        "D1 is 0xFFFFDEAD",
        "D2 is 0xFFFFBEEF",
        "A4 is 0xFFFFCAFE",
        "A5 is 0x00007EAD",
        "SR is S,0,0",
        "(0x2200).W is 0xDEAD",
        "(0x2202).W is 0xBEEF",
        "(0x2204).W is 0xCAFE",
        "(0x2206).W is 0x7EAD",
        "CYCLES is 32"
    });
}

TEST_F(MovemRegisterTestWord, Long) {
    Given({
        "D1 is 0x0000",
        "D2 is 0x0000",
        "A4 is 0x2000",
        "A5 is 0x0000",
        "SR is S,0,0",
        "(0x00102200).W is 0xDEAD",
        "(0x00102202).W is 0xBEEF",
        "(0x00102204).W is 0xCAFE",
        "(0x00102206).W is 0x7EAD"
    });
    When({
        "MOVEM.W (0x00102200).L, D1-D2/A4-A5"
    });
    Then({
        "D1 is 0xFFFFDEAD",
        "D2 is 0xFFFFBEEF",
        "A4 is 0xFFFFCAFE",
        "A5 is 0x00007EAD",
        "SR is S,0,0",
        "(0x00102200).W is 0xDEAD",
        "(0x00102202).W is 0xBEEF",
        "(0x00102204).W is 0xCAFE",
        "(0x00102206).W is 0x7EAD",
        "CYCLES is 36"
    });
}

TEST_F(MovemRegisterTestWord, PCDisplacement) {
    Given({
        "D1 is 0x0000",
        "D2 is 0x0000",
        "A4 is 0x2000",
        "A5 is 0x0000",
        "SR is S,0,0",
        "(0x1200).W is 0xDEAD",
        "(0x1202).W is 0xBEEF",
        "(0x1204).W is 0xCAFE",
        "(0x1206).W is 0x7EAD"
    });
    When({
        "MOVEM.W (0x01FC, PC), D1-D2/A4-A5"
    });
    Then({
        "D1 is 0xFFFFDEAD",
        "D2 is 0xFFFFBEEF",
        "A4 is 0xFFFFCAFE",
        "A5 is 0x00007EAD",
        "SR is S,0,0",
        "(0x1200).W is 0xDEAD",
        "(0x1202).W is 0xBEEF",
        "(0x1204).W is 0xCAFE",
        "(0x1206).W is 0x7EAD",
        "CYCLES is 32"
    });
}

TEST_F(MovemRegisterTestWord, PCIndex) {
    Given({
        "D1 is 0x0000",
        "D2 is 0x0000",
        "A4 is 0x2000",
        "A5 is 0x0000",
        "A6 is 0x01FA",
        "SR is S,0,0",
        "(0x1200).W is 0xDEAD",
        "(0x1202).W is 0xBEEF",
        "(0x1204).W is 0xCAFE",
        "(0x1206).W is 0x7EAD"
    });
    When({
        "MOVEM.W (0x02, PC, A6.L), D1-D2/A4-A5"
    });
    Then({
        "D1 is 0xFFFFDEAD",
        "D2 is 0xFFFFBEEF",
        "A4 is 0xFFFFCAFE",
        "A5 is 0x00007EAD",
        "A6 is 0x000001FA",
        "SR is S,0,0",
        "(0x1200).W is 0xDEAD",
        "(0x1202).W is 0xBEEF",
        "(0x1204).W is 0xCAFE",
        "(0x1206).W is 0x7EAD",
        "CYCLES is 34"
    });
}