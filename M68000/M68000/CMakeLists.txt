set(M68000_INCLUDES
    include/M68000/M68000.h
    include/M68000/Assembler.h
)

set(M68000_SRC
    src/M68000/M68000.cpp
    src/Assembler/Assembler.cpp
    src/Assembler/Assembler_Checks.cpp
    src/Assembler/Assembler_Emit.cpp
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