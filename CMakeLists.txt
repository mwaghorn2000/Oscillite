cmake_minimum_required(VERSION 3.20)
project(Oscillite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.8.1
)

FetchContent_MakeAvailable(catch2)

# ---------------------------------------------------------
# Core library (your DSP / classes)
# ---------------------------------------------------------
add_library(oscillite_core
        src/q8_8.cpp
        src/oscillator.cpp
        src/ADSR.cpp
)

target_include_directories(oscillite_core PUBLIC include)

# ---------------------------------------------------------
# Main executable
# ---------------------------------------------------------
add_executable(Oscillite
        src/main.cpp
)

target_link_libraries(Oscillite PRIVATE oscillite_core)

# ---------------------------------------------------------
# Tests executable
# ---------------------------------------------------------
add_executable(tests
        tests/test_oscillator.cpp
        tests/test_adsr.cpp
        tests/test_q8_8.cpp
)

target_link_libraries(tests
        PRIVATE
        oscillite_core          # <-- gives tests access to q8_8, ADSR, oscillator
        Catch2::Catch2WithMain  # <-- provides main() for Catch2
)

# (Optional but nice) – CTest integration
include(CTest)
include(Catch)
catch_discover_tests(tests)
