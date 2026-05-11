#include "lexer.h"
#include <string>
#include <cctype>
#include "tokenType.h"

Lexer::Lexer(const std::string& input) : input(input)
{
}

void Lexer::advance()
{
	current++;
}

char Lexer::peek()
{
    if (current < input.size()) {
        return input[current];
    }
    return '\0';
}

bool Lexer::isAtEnd()
{
    return current >= input.size();
}

void Lexer::skipWhitespace()
{
	if (isspace(Lexer::peek()))
    {
        Lexer::advance();
    }
}

void Lexer::scanTokens()
{
    while (!Lexer::isAtEnd())
    {
        Lexer::skipWhitespace();
        if (Lexer::isAtEnd()) break;
        char c = Lexer::peek();
        std::string tokenValue(1, c);
        tokenType type = Lexer::createToken(tokenValue);
        Lexer::advance();
    }
}

tokenType Lexer::createToken(const std::string& value)
{
    if (value == "+") return tokenType::PLUS;
    if (value == "-") return tokenType::MINUS;
    if (value == "*") return tokenType::STAR;
    if (value == "/") return tokenType::SLASH;
    if (value == "(") return tokenType::LPAREN;
    if (value == ")") return tokenType::RPAREN;

    // Check if the string represents a number (integer or floating)
    if (!value.empty()) {
        bool hasDigits = false;
        bool hasDot = false;
        for (char c : value) {
            if (std::isdigit(static_cast<unsigned char>(c))) {
                hasDigits = true;
            }
            else if (c == '.') {
                if (hasDot) { hasDigits = false; break; } // more than one dot -> not a number
                hasDot = true;
            }
            else {
                hasDigits = false;
                break;
            }
        }
        if (hasDigits) return tokenType::NUMBER;
    }

    return tokenType::EOF_TOKEN;
}


