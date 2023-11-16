# Compiler
set(COMPILER_INCLUDES
)

set(COMPILER_SRC
    src/Compiler/CompilerTest.cpp
)

# Parser files
set(PARSER_TEST_INCLUDES
    include/Assembler/Parser/Instructions/InstructionsTest.h
)

set(PARSER_INSTRUCTIONS_TEST_SRC
    src/Parser/Instructions/InstructionsTest.cpp
    src/Parser/Instructions/AbcdTest.cpp
    src/Parser/Instructions/AddaTest.cpp
    src/Parser/Instructions/AddiTest.cpp
    src/Parser/Instructions/AddqTest.cpp
    src/Parser/Instructions/AddxTest.cpp
    src/Parser/Instructions/AddTest.cpp
    src/Parser/Instructions/AndiTest.cpp
    src/Parser/Instructions/AndTest.cpp
    src/Parser/Instructions/AslTest.cpp
    src/Parser/Instructions/AsrTest.cpp
    src/Parser/Instructions/BccTest.cpp
    src/Parser/Instructions/BchgTest.cpp
    src/Parser/Instructions/BclrTest.cpp
    src/Parser/Instructions/BraTest.cpp
    src/Parser/Instructions/BsetTest.cpp
    src/Parser/Instructions/BsrTest.cpp
    src/Parser/Instructions/BtstTest.cpp
    src/Parser/Instructions/ChkTest.cpp
    src/Parser/Instructions/ClrTest.cpp
    src/Parser/Instructions/CmpaTest.cpp
    src/Parser/Instructions/CmpiTest.cpp
    src/Parser/Instructions/CmpmTest.cpp
    src/Parser/Instructions/CmpTest.cpp
    src/Parser/Instructions/DBccTest.cpp
    src/Parser/Instructions/DivsTest.cpp
    src/Parser/Instructions/DivuTest.cpp
    src/Parser/Instructions/EoriTest.cpp
    src/Parser/Instructions/EorTest.cpp
    src/Parser/Instructions/ExgTest.cpp
    src/Parser/Instructions/ExtTest.cpp
    src/Parser/Instructions/IllegalTest.cpp
    src/Parser/Instructions/JmpTest.cpp
    src/Parser/Instructions/JsrTest.cpp
    src/Parser/Instructions/LeaTest.cpp
    src/Parser/Instructions/LinkTest.cpp
    src/Parser/Instructions/LslTest.cpp
    src/Parser/Instructions/LsrTest.cpp
    src/Parser/Instructions/MoveaTest.cpp
    src/Parser/Instructions/MoveCcrTest.cpp
    src/Parser/Instructions/MovemTest.cpp
    src/Parser/Instructions/MovepTest.cpp
    src/Parser/Instructions/MoveqTest.cpp
    src/Parser/Instructions/MoveSrTest.cpp
    src/Parser/Instructions/MoveUspTest.cpp
    src/Parser/Instructions/MoveTest.cpp
    src/Parser/Instructions/MulsTest.cpp
    src/Parser/Instructions/MuluTest.cpp
    src/Parser/Instructions/NbcdTest.cpp
    src/Parser/Instructions/NegxTest.cpp
    src/Parser/Instructions/NegTest.cpp
    src/Parser/Instructions/NopTest.cpp
    src/Parser/Instructions/NotTest.cpp
    src/Parser/Instructions/OriTest.cpp
    src/Parser/Instructions/OrTest.cpp
    src/Parser/Instructions/PeaTest.cpp
    src/Parser/Instructions/ResetTest.cpp
    src/Parser/Instructions/RolTest.cpp
    src/Parser/Instructions/RoxlTest.cpp
    src/Parser/Instructions/RoxrTest.cpp
    src/Parser/Instructions/RorTest.cpp
    src/Parser/Instructions/RteTest.cpp
    src/Parser/Instructions/RtrTest.cpp
    src/Parser/Instructions/RtsTest.cpp
    src/Parser/Instructions/SbcdTest.cpp
    src/Parser/Instructions/SccTest.cpp
    src/Parser/Instructions/StopTest.cpp
    src/Parser/Instructions/SubaTest.cpp
    src/Parser/Instructions/SubiTest.cpp
    src/Parser/Instructions/SubqTest.cpp
    src/Parser/Instructions/SubxTest.cpp
    src/Parser/Instructions/SubTest.cpp
    src/Parser/Instructions/SwapTest.cpp
    src/Parser/Instructions/TasTest.cpp
    src/Parser/Instructions/TrapvTest.cpp
    src/Parser/Instructions/TrapTest.cpp
    src/Parser/Instructions/TstTest.cpp
    src/Parser/Instructions/UnlkTest.cpp
)

# Add executable
add_executable(AssemblerTest
    ${COMPILER_INCLUDES}
    ${COMPILER_SRC}
    ${PARSER_TEST_INCLUDES}
    ${PARSER_INSTRUCTIONS_TEST_SRC}
)

target_include_directories(AssemblerTest
    PRIVATE
    include
)

target_compile_options(
    AssemblerTest
    PRIVATE
    ${PROCESSORS_COMPILER_FLAGS}
)

target_link_libraries(AssemblerTest
    M68000 gtest gtest_main gmock_main
)

add_test(NAME AssemblerTest COMMAND AssemblerTest)
