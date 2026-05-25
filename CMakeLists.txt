cmake_minimum_required(VERSION 3.10)

project(cpp_interpreter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    interpreter
    src/main/main.cpp
    src/lexer/lexer.cpp
 )