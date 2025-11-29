cmake_minimum_required(VERSION 3.20)
project(cpp_engineering LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cpp_engineering src/main.cpp
        src/q8_8.cpp
        include/q8_8.h
        src/func_g.cpp
        include/func_g.h)
target_include_directories(cpp_engineering PRIVATE include)