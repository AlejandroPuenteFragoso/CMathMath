#include "lexer.h"
#include <string>
#include <cctype>
#include <stdexcept>
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

char Lexer::peekNext()
{
    if (current + 1 < input.size()) {
        return input[current + 1];
    }
    return '\0';
}

bool Lexer::isAtEnd()
{
    return current >= input.size();
}

void Lexer::skipWhitespace()
{
    while (std::isspace(static_cast<unsigned char>(peek())))
    {
        advance();
    }
}

const std::vector<Token>& Lexer::getTokens() const
{
    return tokens;
}

void Lexer::scanNumber()
{
    bool hasDot = false;

    // Consume integer part
    while (std::isdigit(peek())) {
        advance();
    }

    // Optional decimal part
    if (peek() == '.') {

        if (hasDot) {
            throw std::runtime_error("Invalid number format: multiple decimal points");
        }

        hasDot = true;
        advance(); // consume '.'

        // Require at least one digit after '.'
        if (!std::isdigit(peek())) {
            throw std::runtime_error("Invalid number format");
        }

        while (std::isdigit(peek())) {
            advance();
        }
    }

    // Detect second decimal point
    if (peek() == '.') {
        throw std::runtime_error("Invalid number format: multiple decimal points");
    }

    std::string lexeme = input.substr(start, current - start);

    tokens.push_back(Token(tokenType::NUMBER, lexeme));
}

void Lexer::scanIdentifier()
{
    while (std::isalnum(static_cast<unsigned char>(peek())) || peek() == '_') {
        advance();
    }

    std::string lexeme = input.substr(start, current - start);
    tokens.push_back(Token(createToken(lexeme), lexeme));
}

void Lexer::scanTokens()
{
    while (!isAtEnd()) {
        skipWhitespace();
        if (isAtEnd()) break;

		start = current;  // avoid blank spaces on the left of the lexeme

        if (std::isdigit(peek())) {
            scanNumber();
            continue;
        }

        if (std::isalpha(static_cast<unsigned char>(peek())) || peek() == '_') {
            scanIdentifier();
            continue;
        }

        char c = peek();
        advance();

        // Handle multi-character operators: ==, !=, <=, >=
        std::string tokenValue;
        switch (c) {
        case '=':
            if (peek() == '=') { advance(); tokenValue = "=="; }
            else { tokenValue = "="; }
            break;
        case '!':
            if (peek() == '=') { advance(); tokenValue = "!="; }
            else { tokenValue = "!"; }
            break;
        case '<':
            if (peek() == '=') { advance(); tokenValue = "<="; }
            else { tokenValue = "<"; }
            break;
        case '>':
            if (peek() == '=') { advance(); tokenValue = ">="; }
            else { tokenValue = ">"; }
            break;
        default:
            tokenValue = std::string(1, c);
            break;
        }

        tokenType type = createToken(tokenValue);
        tokens.push_back(Token(type, tokenValue));
    }
    tokens.push_back(Token(tokenType::EOF_TOKEN, ""));
}

tokenType Lexer::createToken(const std::string& value)
{
    if (value == "+") return tokenType::PLUS;
    if (value == "-") return tokenType::MINUS;
    if (value == "*") return tokenType::STAR;
    if (value == "/") return tokenType::SLASH;
    if (value == "(") return tokenType::LPAREN;
    if (value == ")") return tokenType::RPAREN;
    if (value == "!") return tokenType::BANG;
    // Comparison / equality operators
    if (value == "==") return tokenType::EQUAL_EQUAL;
    if (value == "!=") return tokenType::BANG_EQUAL;
    if (value == "<") return tokenType::LESS;
    if (value == "<=") return tokenType::LESS_EQUAL;
    if (value == ">") return tokenType::GREATER;
    if (value == ">=") return tokenType::GREATER_EQUAL;
    if (value == "true") return tokenType::TRUE;
    if (value == "false") return tokenType::FALSE;
    if (value == "nil") return tokenType::NIL;

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

    throw std::runtime_error(
        "Unexpected character: " + value
    );
}


