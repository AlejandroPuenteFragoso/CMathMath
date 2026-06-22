# Esqueleto de tests para CMathMath.
# Usa doctest (single-header) traído con FetchContent: no hay que instalar nada.
include(FetchContent)

# doctest v2.4.11 declara un cmake_minimum_required antiguo; este ajuste permite
# que sea configurable por versiones modernas de CMake (>= 4.0).
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG        v2.4.11
)
FetchContent_MakeAvailable(doctest)

add_executable(cmathmath_tests
    test_main.cpp
    test_lexer.cpp
    test_parser.cpp
    test_evaluator.cpp
    # Fuentes del proyecto bajo prueba (expr.h es header-only):
    ${CMAKE_SOURCE_DIR}/src/lexer/lexer.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/parser.cpp
)

# Permite incluir como "lexer/lexer.h", "parser/parser.h", etc.
target_include_directories(cmathmath_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(cmathmath_tests PRIVATE doctest::doctest)

add_test(NAME cmathmath_tests COMMAND cmathmath_tests)
