// Tests de evaluación: comprueban el resultado numérico de evaluar el AST.
#include <doctest/doctest.h>
#include <string>
#include "lexer/lexer.h"
#include "parser/parser.h"

// Helper: de texto fuente al valor evaluado.
static double eval(const std::string& src) {
    Lexer lexer(src);
    lexer.scanTokens();
    Parser parser(lexer.getTokens());
    return parser.parse()->eval();
}

TEST_CASE("Evaluador: aritmética básica") {
    CHECK(eval("2 + 3")  == doctest::Approx(5.0));
    CHECK(eval("10 - 4") == doctest::Approx(6.0));
    CHECK(eval("6 * 7")  == doctest::Approx(42.0));
    CHECK(eval("8 / 2")  == doctest::Approx(4.0));
}

TEST_CASE("Evaluador: respeta la precedencia y los paréntesis") {
    CHECK(eval("2 + 3 * 4")   == doctest::Approx(14.0));
    CHECK(eval("(2 + 3) * 4") == doctest::Approx(20.0));
}

TEST_CASE("Evaluador: el menos unario funciona") {
    CHECK(eval("-5")     == doctest::Approx(-5.0));
    CHECK(eval("3 * -2") == doctest::Approx(-6.0));
}

TEST_CASE("Evaluador: la división por cero lanza error") {
    CHECK_THROWS(eval("1 / 0"));
}

// TODO(Alex, #15): comparaciones e igualdad deben evaluar a 1.0 (true) / 0.0 (false).
// TODO(Alex, #16): truthiness de booleanos y nil; comportamiento del operador !.
// TODO(Alex, #17): tras corregir la doble evaluación, añadir un test con efectos
//   secundarios que falle si el operando derecho se evalúa dos veces.
