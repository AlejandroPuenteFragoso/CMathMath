// Tests del Parser. Comprueban que una cadena de tokens válida produce un AST
// y que las entradas mal formadas son rechazadas.
#include <doctest/doctest.h>
#include <memory>
#include <string>
#include "lexer/lexer.h"
#include "parser/parser.h"

// Helper: de texto fuente a AST.
static std::unique_ptr<Expr> parse(const std::string& src) {
    Lexer lexer(src);
    lexer.scanTokens();
    Parser parser(lexer.getTokens());
    return parser.parse();
}

TEST_CASE("Parser: una expresión válida construye un AST") {
    auto ast = parse("(1 + 2) * 3");
    REQUIRE(ast != nullptr);
}

TEST_CASE("Parser: tokens sobrantes son un error") {
    CHECK_THROWS(parse("1 2"));
}

TEST_CASE("Parser: falta el paréntesis de cierre") {
    CHECK_THROWS(parse("(1 + 2"));
}

TEST_CASE("Parser: un operador sin operando derecho es un error") {
    CHECK_THROWS(parse("3 +"));
}

TEST_CASE("Parser: igualdad tiene menor precedencia que suma") {
    auto ast = parse("1 + 1 == 2");

    auto* equality = dynamic_cast<Binary*>(ast.get());
    REQUIRE(equality != nullptr);
    CHECK(equality->op.type == tokenType::EQUAL_EQUAL);

    auto* addition = dynamic_cast<Binary*>(equality->left.get());
    REQUIRE(addition != nullptr);
    CHECK(addition->op.type == tokenType::PLUS);

    auto* right = dynamic_cast<Literal*>(equality->right.get());
    REQUIRE(right != nullptr);
    REQUIRE(std::holds_alternative<double>(right->value));
    CHECK(std::get<double>(right->value) == 2.0);
}

TEST_CASE("Parser: comparacion tiene mayor precedencia que igualdad") {
    auto ast = parse("1 == 2 < 3");

    auto* equality = dynamic_cast<Binary*>(ast.get());
    REQUIRE(equality != nullptr);
    CHECK(equality->op.type == tokenType::EQUAL_EQUAL);

    auto* comparison = dynamic_cast<Binary*>(equality->right.get());
    REQUIRE(comparison != nullptr);
    CHECK(comparison->op.type == tokenType::LESS);
}

TEST_CASE("Parser: construye literales booleanos y nil") {
    auto trueAst = parse("true");
    auto* trueLiteral = dynamic_cast<Literal*>(trueAst.get());
    REQUIRE(trueLiteral != nullptr);
    REQUIRE(std::holds_alternative<bool>(trueLiteral->value));
    CHECK(std::get<bool>(trueLiteral->value));

    auto nilAst = parse("nil");
    auto* nilLiteral = dynamic_cast<Literal*>(nilAst.get());
    REQUIRE(nilLiteral != nullptr);
    CHECK(std::holds_alternative<std::monostate>(nilLiteral->value));
}

TEST_CASE("Parser: construye negación lógica unaria") {
    auto ast = parse("!false");
    auto* unary = dynamic_cast<Unary*>(ast.get());
    REQUIRE(unary != nullptr);
    CHECK(unary->op.type == tokenType::BANG);

    auto* literal = dynamic_cast<Literal*>(unary->right.get());
    REQUIRE(literal != nullptr);
    REQUIRE(std::holds_alternative<bool>(literal->value));
    CHECK_FALSE(std::get<bool>(literal->value));
}
// TODO(Alex, #27): tras renombrar term/factor para alinearlos con la gramática,
//   añadir tests de asociatividad que fijen la precedencia (p. ej. 2 - 3 - 4).
