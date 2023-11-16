#include "Assembler/Parser/Instructions/InstructionsTest.h"

#include "M68000/Assembler.h"

using namespace rbrown::m68000;

TEST_P(PositiveTest, ParsesInstruction) {
    const auto sourceLine = GetParam();
    Instruction instruction;
    const auto result = Assemble(sourceLine, instruction);
    ASSERT_TRUE(result) << sourceLine;
}

TEST_P(NegativeTest, DoesNotParseInstruction) {
    const auto sourceLine = GetParam();
    Instruction instruction;
    const auto result = Assemble(sourceLine, instruction);
    ASSERT_FALSE(result) << sourceLine;
}