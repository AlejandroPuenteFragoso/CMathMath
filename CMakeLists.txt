cmake_minimum_required(VERSION 3.10)

project(cpp_interpreter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    interpreter
    src/main/main.cpp
    src/lexer/lexer.cpp
  "src/ast/expr.h" "src/parser/parser.h" "src/parser/parser.cpp")

# Tests (opcional). Configurar con: cmake -B build -DBUILD_TESTING=ON
option(BUILD_TESTING "Compilar la suite de tests" OFF)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()