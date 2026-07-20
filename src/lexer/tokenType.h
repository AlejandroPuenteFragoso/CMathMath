#pragma once
#include <string>
enum class tokenType
{
	NUMBER,
	PLUS,
	MINUS,
	STAR,
	SLASH,
	LPAREN,
	RPAREN,
    EQUAL_EQUAL,
    BANG_EQUAL,
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,
	EOF_TOKEN,

};

inline std::string tokenTypeToString(tokenType type)
{
    switch (type) {
    case tokenType::NUMBER:
        return "NUMBER";
    case tokenType::PLUS:
        return "PLUS";
    case tokenType::MINUS:
        return "MINUS";
    case tokenType::STAR:
        return "STAR";
    case tokenType::SLASH:
        return "SLASH";
    case tokenType::LPAREN:
        return "LPAREN";
    case tokenType::RPAREN:
        return "RPAREN";
    case tokenType::EQUAL_EQUAL:
        return "EQUAL_EQUAL";
    case tokenType::BANG_EQUAL:
        return "BANG_EQUAL";
    case tokenType::LESS:
        return "LESS";
    case tokenType::LESS_EQUAL:
        return "LESS_EQUAL";
    case tokenType::GREATER:
        return "GREATER";
    case tokenType::GREATER_EQUAL:
        return "GREATER_EQUAL";
    case tokenType::EOF_TOKEN:
        return "EOF_TOKEN";
    default:
        return "UNKNOWN";
    }
}
