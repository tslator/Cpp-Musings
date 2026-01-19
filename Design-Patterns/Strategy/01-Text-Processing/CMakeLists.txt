cmake_minimum_required(VERSION 4.0)
project(01_Text_Processing)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
# --- Catch2 Integration ---
FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2 # or latest release
)

# --- FmtLib Integration ---
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 11.0.2
)

# --- Ranges V3 Integration ---
FetchContent_Declare(
        range_v3
        GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
        GIT_TAG 0.12.0 # latest stable release as of now
        GIT_SUBMODULES ""
)

FetchContent_MakeAvailable(catch2 fmt range_v3)

add_executable(01_Text_Processing main.cpp
        strategy.cpp
        strategy.h)
target_link_libraries(01_Text_Processing PRIVATE fmt::fmt range-v3)

file(GLOB TEST_SOURCES tests/*.cpp)
add_executable(tests ${TEST_SOURCES}
        tests/test_test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
