add_executable(DisassemblerTest
    src/DisassemblerTest.cpp
    )

target_include_directories(DisassemblerTest
    PRIVATE
    include
    )

target_compile_options(
    DisassemblerTest
    PRIVATE
    ${PROCESSORS_COMPILER_FLAGS}
)

target_link_libraries(DisassemblerTest
    M68000 gtest gtest_main gmock_main
    )

add_test(NAME DisassemblerTest COMMAND DisassemblerTest)
