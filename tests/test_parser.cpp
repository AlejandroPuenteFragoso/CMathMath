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
    CHECK_THROWS_WITH(
        parse("1 2"),
        "Error [line 1, column 3]: Unexpected token '2' after expression"
    );
}

TEST_CASE("Parser: falta el paréntesis de cierre") {
    CHECK_THROWS_WITH(
        parse("(3 + 4"),
        "Error [line 1, column 7]: Expected ')' after expression"
    );
}

TEST_CASE("Parser: un operador sin operando derecho es un error") {
    CHECK_THROWS_WITH(
        parse("3 +"),
        "Error [line 1, column 4]: Expected expression, found <end of input>"
    );
}

TEST_CASE("Parser: an unexpected token includes its position") {
    CHECK_THROWS_WITH(
        parse("1 + * 2"),
        "Error [line 1, column 5]: Expected expression, found '*'"
    );
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

TEST_CASE("Parser: rechaza comparaciones de orden encadenadas") {
    CHECK_THROWS_WITH(
        parse("1 < 2 < 3"),
        "Error [line 1, column 7]: Chained comparisons are not supported"
    );
    CHECK_THROWS_WITH(
        parse("3 > 2 >= 1"),
        "Error [line 1, column 7]: Chained comparisons are not supported"
    );
    CHECK_THROWS_WITH(
        parse("1 <= 2 > 0"),
        "Error [line 1, column 8]: Chained comparisons are not supported"
    );
}

TEST_CASE("Parser: rechaza igualdades encadenadas") {
    CHECK_THROWS_WITH(
        parse("1 == 1 == true"),
        "Error [line 1, column 8]: Chained comparisons are not supported"
    );
    CHECK_THROWS_WITH(
        parse("1 != 2 != false"),
        "Error [line 1, column 8]: Chained comparisons are not supported"
    );
}

TEST_CASE("Parser: permite comparaciones agrupadas o en distintos niveles") {
    CHECK_NOTHROW(parse("1 < 2 == true"));
    CHECK_NOTHROW(parse("(1 < 2) == true"));
    CHECK_NOTHROW(parse("(1 < 2) == (2 < 3)"));
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

TEST_CASE("Parser: resta y división son asociativas por la izquierda") {
    auto subtractionAst = parse("10 - 3 - 2");
    auto* subtraction = dynamic_cast<Binary*>(subtractionAst.get());
    REQUIRE(subtraction != nullptr);
    CHECK(subtraction->op.type == tokenType::MINUS);

    auto* subtractionLeft = dynamic_cast<Binary*>(subtraction->left.get());
    REQUIRE(subtractionLeft != nullptr);
    CHECK(subtractionLeft->op.type == tokenType::MINUS);

    auto divisionAst = parse("16 / 4 / 2");
    auto* division = dynamic_cast<Binary*>(divisionAst.get());
    REQUIRE(division != nullptr);
    CHECK(division->op.type == tokenType::SLASH);

    auto* divisionLeft = dynamic_cast<Binary*>(division->left.get());
    REQUIRE(divisionLeft != nullptr);
    CHECK(divisionLeft->op.type == tokenType::SLASH);
}
