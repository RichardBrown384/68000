cmake_minimum_required(VERSION 3.21)

project(Processors CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(PROCESSORS_BUILD_TESTS "Build tests for processors" ON)

include(FetchContent)

#set(FETCHCONTENT_FULLY_DISCONNECTED true)

if(PROCESSORS_BUILD_TESTS)

    enable_testing()

    FetchContent_Declare(googletest
        GIT_REPOSITORY     https://github.com/google/googletest.git
        GIT_TAG            main
        CMAKE_ARGS         -Dgtest_force_shared_crt=ON -DCMAKE_CXX_STANDARD=23
        )

    FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG develop
        )

    FetchContent_MakeAvailable(googletest json)
endif()

FetchContent_Declare(fmtlib
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 10.1.1
    )
FetchContent_MakeAvailable(fmtlib)

if(MSVC)
    set(PROCESSORS_COMPILER_FLAGS
        /Wall
        /wd4100 /wd4514 /wd4710 /wd4820
        /experimental:external /external:W0
        )
else()
    set(PROCESSORS_COMPILER_FLAGS
        -Wall -Wextra -pedantic -Werror
        -Wno-unused-parameter
        )
endif()

add_subdirectory(M68000)
