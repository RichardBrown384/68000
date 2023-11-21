set(M68000_INCLUDES
    include/M68000/M68000.h
    include/M68000/Assembler.h
)

set(M68000_SRC
    src/Assembler/Assembler.cpp
    src/Assembler/Assembler_Checks.cpp
    src/Assembler/Assembler_Emit.cpp
    src/Disassembler/Disassembler.cpp
    src/Disassembler/Disassembler_Line0.cpp
    src/Disassembler/Disassembler_Line1.cpp
    src/Disassembler/Disassembler_Line2.cpp
    src/Disassembler/Disassembler_Line3.cpp
    src/Disassembler/Disassembler_Line4.cpp
    src/Disassembler/Disassembler_Line5.cpp
    src/Disassembler/Disassembler_Line6.cpp
    src/Disassembler/Disassembler_Line7.cpp
    src/Disassembler/Disassembler_Line8.cpp
    src/Disassembler/Disassembler_Line9.cpp
    src/Disassembler/Disassembler_LineB.cpp
    src/Disassembler/Disassembler_LineC.cpp
    src/Disassembler/Disassembler_LineD.cpp
    src/Disassembler/Disassembler_LineE.cpp
    src/M68000/M68000.cpp
    )

add_library(M68000 STATIC
    ${M68000_INCLUDES}
    ${M68000_SRC}
)

target_include_directories(M68000
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_options(
    M68000
    PRIVATE
    ${PROCESSORS_COMPILER_FLAGS}
)

target_link_libraries(
    M68000
    PRIVATE
    fmt::fmt
)

install(TARGETS M68000 EXPORT M68000Config DESTINATION lib)
install(FILES ${M68000_INCLUDES} DESTINATION include/M68000)

export(TARGETS M68000
    NAMESPACE M68000::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/M68000Config.cmake"
)

install(EXPORT M68000Config
    NAMESPACE M68000::
    DESTINATION lib/cmake/M68000
)