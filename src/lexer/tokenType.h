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
	RPAREN ,
	EOF_TOKEN,
    UNKNOWN,

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
        case tokenType::EOF_TOKEN:
            return "EOF_TOKEN";
        case tokenType::UNKNOWN:
            return "UNKNOWN";
        default:
            return "UNDEFINED";
    }
}