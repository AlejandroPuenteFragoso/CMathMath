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

// TODO(Alex, #27): tras renombrar term/factor para alinearlos con la gramática,
//   añadir tests de asociatividad que fijen la precedencia (p. ej. 2 - 3 - 4).
