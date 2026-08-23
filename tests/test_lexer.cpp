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
    CHECK(tokens[0].line == 1);
    CHECK(tokens[0].column == 1);
    CHECK(tokens[1].type == tokenType::PLUS);
    CHECK(tokens[1].line == 1);
    CHECK(tokens[1].column == 2);
    CHECK(tokens[2].type == tokenType::NUMBER);
    CHECK(tokens[2].line == 1);
    CHECK(tokens[2].column == 3);
    CHECK(tokens[3].type == tokenType::EOF_TOKEN);
    CHECK(tokens[3].line == 1);
    CHECK(tokens[3].column == 4);
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

TEST_CASE("Lexer: preserves the initial position across multiple lines") {
    Lexer lexer("12 +\n  true <= 3.5");
    lexer.scanTokens();
    const auto& tokens = lexer.getTokens();

    REQUIRE(tokens.size() == 6);

    CHECK(tokens[0].lexeme == "12");
    CHECK(tokens[0].line == 1);
    CHECK(tokens[0].column == 1);

    CHECK(tokens[1].lexeme == "+");
    CHECK(tokens[1].line == 1);
    CHECK(tokens[1].column == 4);

    CHECK(tokens[2].lexeme == "true");
    CHECK(tokens[2].line == 2);
    CHECK(tokens[2].column == 3);

    CHECK(tokens[3].lexeme == "<=");
    CHECK(tokens[3].line == 2);
    CHECK(tokens[3].column == 8);

    CHECK(tokens[4].lexeme == "3.5");
    CHECK(tokens[4].line == 2);
    CHECK(tokens[4].column == 11);

    CHECK(tokens[5].type == tokenType::EOF_TOKEN);
    CHECK(tokens[5].line == 2);
    CHECK(tokens[5].column == 14);
}


 TEST_CASE("Lexer: un caracter invalido lanza error") {
     Lexer lexer("2 @ 3");
     CHECK_THROWS(lexer.scanTokens());
 }

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
TEST_CASE("Lexer: reconoce booleanos, nil y el operador lógico") {
    Lexer lexer("true false nil !");
    lexer.scanTokens();
    const auto& tokens = lexer.getTokens();

    REQUIRE(tokens.size() == 5);
    CHECK(tokens[0].type == tokenType::TRUE);
    CHECK(tokens[0].lexeme == "true");
    CHECK(tokens[1].type == tokenType::FALSE);
    CHECK(tokens[1].lexeme == "false");
    CHECK(tokens[2].type == tokenType::NIL);
    CHECK(tokens[2].lexeme == "nil");
    CHECK(tokens[3].type == tokenType::BANG);
    CHECK(tokens[3].lexeme == "!");
    CHECK(tokens[4].type == tokenType::EOF_TOKEN);
}

TEST_CASE("Lexer rechaza caracteres invalidos") {
    Lexer lexerEqual("5 = 5");
    CHECK_THROWS_WITH(
        lexerEqual.scanTokens(),
        "Error [line 1, column 3]: Unexpected character: ="
    );

    Lexer lexerUnknown("5 @ 5");
    CHECK_THROWS_WITH(
        lexerUnknown.scanTokens(),
        "Error [line 1, column 3]: Unexpected character: @"
    );
}

TEST_CASE("Lexer: errors include the exact position") {
    Lexer lexerUnknown("1 +\n  @");
    CHECK_THROWS_WITH(
        lexerUnknown.scanTokens(),
        "Error [line 2, column 3]: Unexpected character: @"
    );

    Lexer lexerInvalidNumber("1.2.3");
    CHECK_THROWS_WITH(
        lexerInvalidNumber.scanTokens(),
        "Error [line 1, column 4]: Invalid number format: multiple decimal points"
    );
}

TEST_CASE("Lexer rechaza palabras desconocidas") {
    Lexer lexer("truth");
    CHECK_THROWS_WITH(
        lexer.scanTokens(),
        "Error [line 1, column 1]: Unexpected character: truth"
    );
}
