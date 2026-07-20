// Tests del Lexer. Los TEST_CASE de abajo son ejemplos funcionales que sirven
// de plantilla; los comentarios TODO marcan lo que falta por cubrir (issue #19).
#include <doctest/doctest.h>
#include "lexer/lexer.h"

TEST_CASE("Lexer: tokeniza una suma simple") {
    Lexer lexer("1+2");
    lexer.scanTokens();
    const auto& tokens = lexer.getTokens();

    REQUIRE(tokens.size() == 4); // NUMBER PLUS NUMBER EOF
    CHECK(tokens[0].type == tokenType::NUMBER);
    CHECK(tokens[0].lexeme == "1");
    CHECK(tokens[1].type == tokenType::PLUS);
    CHECK(tokens[2].type == tokenType::NUMBER);
    CHECK(tokens[3].type == tokenType::EOF_TOKEN);
}

TEST_CASE("Lexer: reconoce números decimales de varios dígitos") {
    Lexer lexer("3.14");
    lexer.scanTokens();
    const auto& tokens = lexer.getTokens();

    REQUIRE(tokens.size() == 2); // NUMBER EOF
    CHECK(tokens[0].type == tokenType::NUMBER);
    CHECK(tokens[0].lexeme == "3.14");
}

TEST_CASE("Lexer: ignora los espacios en blanco") {
    Lexer lexer("  7   *  ( 8 )  ");
    lexer.scanTokens();
    const auto& tokens = lexer.getTokens();

    REQUIRE(tokens.size() == 6); // NUMBER STAR LPAREN NUMBER RPAREN EOF
    CHECK(tokens[0].lexeme == "7");
    CHECK(tokens[1].type == tokenType::STAR);
    CHECK(tokens[2].type == tokenType::LPAREN);
}

// TODO(Alex, #26): un carácter inválido debe lanzar un error, no producir un EOF_TOKEN.
//   Cuando #26 esté resuelto, descomenta este caso:
// TEST_CASE("Lexer: un caracter invalido lanza error") {
//     Lexer lexer("2 @ 3");
//     CHECK_THROWS(lexer.scanTokens());
// }

TEST_CASE("Lexer: reconoce operadores de comparacion e igualdad") {
    Lexer lexer("< <= > >= == !=");
    lexer.scanTokens();

    const auto& tokens = lexer.getTokens();

    REQUIRE(tokens.size() == 7);

    CHECK(tokens[0].type == tokenType::LESS);
    CHECK(tokens[0].lexeme == "<");

    CHECK(tokens[1].type == tokenType::LESS_EQUAL);
    CHECK(tokens[1].lexeme == "<=");

    CHECK(tokens[2].type == tokenType::GREATER);
    CHECK(tokens[2].lexeme == ">");

    CHECK(tokens[3].type == tokenType::GREATER_EQUAL);
    CHECK(tokens[3].lexeme == ">=");

    CHECK(tokens[4].type == tokenType::EQUAL_EQUAL);
    CHECK(tokens[4].lexeme == "==");

    CHECK(tokens[5].type == tokenType::BANG_EQUAL);
    CHECK(tokens[5].lexeme == "!=");

    CHECK(tokens[6].type == tokenType::EOF_TOKEN);
    CHECK(tokens[6].lexeme.empty());
}
// TODO(Alex, #16): añadir casos para las palabras clave true/false/nil y el operador !.
