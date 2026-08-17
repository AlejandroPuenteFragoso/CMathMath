// Tests de evaluación: comprueban los valores producidos por el AST.
#include <doctest/doctest.h>
#include <string>
#include "lexer/lexer.h"
#include "parser/parser.h"

// Helper: de texto fuente al valor evaluado.
static Value eval(const std::string& src) {
    Lexer lexer(src);
    lexer.scanTokens();
    Parser parser(lexer.getTokens());
    return parser.parse()->eval();
}

static double evalNumber(const std::string& src) {
    return std::get<double>(eval(src));
}

static bool evalBoolean(const std::string& src) {
    return std::get<bool>(eval(src));
}

TEST_CASE("Evaluador: aritmética básica") {
    CHECK(evalNumber("2 + 3")  == doctest::Approx(5.0));
    CHECK(evalNumber("10 - 4") == doctest::Approx(6.0));
    CHECK(evalNumber("6 * 7")  == doctest::Approx(42.0));
    CHECK(evalNumber("8 / 2")  == doctest::Approx(4.0));
}

TEST_CASE("Evaluador: respeta la precedencia y los paréntesis") {
    CHECK(evalNumber("2 + 3 * 4")   == doctest::Approx(14.0));
    CHECK(evalNumber("(2 + 3) * 4") == doctest::Approx(20.0));
}

TEST_CASE("Evaluador: resta y división son asociativas por la izquierda") {
    CHECK(evalNumber("10 - 3 - 2") == doctest::Approx(5.0));
    CHECK(evalNumber("16 / 4 / 2") == doctest::Approx(2.0));
}

TEST_CASE("Evaluador: el menos unario funciona") {
    CHECK(evalNumber("-5")     == doctest::Approx(-5.0));
    CHECK(evalNumber("3 * -2") == doctest::Approx(-6.0));
}

TEST_CASE("Evaluador: la división por cero lanza error") {
    CHECK_THROWS(eval("1 / 0"));
}

TEST_CASE("Evaluador: comparaciones devuelven booleanos") {
    CHECK(evalBoolean("3 < 4"));
    CHECK_FALSE(evalBoolean("4 < 3"));
    CHECK(evalBoolean("3 <= 3"));
    CHECK_FALSE(evalBoolean("4 <= 3"));
    CHECK(evalBoolean("4 > 3"));
    CHECK_FALSE(evalBoolean("3 > 4"));
    CHECK(evalBoolean("3 >= 3"));
    CHECK_FALSE(evalBoolean("3 >= 4"));
}

TEST_CASE("Evaluador: igualdad y desigualdad devuelven booleanos") {
    CHECK(evalBoolean("5 == 5"));
    CHECK_FALSE(evalBoolean("5 == 4"));
    CHECK(evalBoolean("5 != 4"));
    CHECK_FALSE(evalBoolean("5 != 5"));
}

TEST_CASE("Evaluador: respeta precedencia en expresiones relacionales") {
    CHECK(evalBoolean("1 + 1 == 2"));
    CHECK(evalBoolean("1 + 2 * 3 == 7"));
    CHECK_FALSE(evalBoolean("1 + 2 > 2 * 2"));
    CHECK(evalBoolean("(1 + 2) * 3 <= 9"));
}

TEST_CASE("Evaluador: reconoce booleanos y nil") {
    CHECK(evalBoolean("true"));
    CHECK_FALSE(evalBoolean("false"));
    CHECK(std::holds_alternative<std::monostate>(eval("nil")));
}

TEST_CASE("Evaluador: aplica truthiness al operador lógico") {
    CHECK_FALSE(evalBoolean("!true"));
    CHECK(evalBoolean("!false"));
    CHECK(evalBoolean("!nil"));
    CHECK_FALSE(evalBoolean("!0"));
    CHECK(evalBoolean("!!true"));
}

TEST_CASE("Evaluador: compara booleanos y nil") {
    CHECK(evalBoolean("true == true"));
    CHECK(evalBoolean("false != true"));
    CHECK(evalBoolean("nil == nil"));
    CHECK_FALSE(evalBoolean("nil == false"));
}

TEST_CASE("Evaluador: rechaza tipos no numéricos en aritmética") {
    CHECK_THROWS(eval("true + 1"));
    CHECK_THROWS(eval("-nil"));
}

TEST_CASE("Evaluador: no acepta ! como operador binario") {
    CHECK_THROWS(eval("3 ! 2"));
}

// TODO(Alex, #17): tras corregir la doble evaluación, añadir un test con efectos
//   secundarios que falle si el operando derecho se evalúa dos veces.
