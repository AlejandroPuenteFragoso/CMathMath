#pragma once
#include <string>

/**
 * @brief Categories of the lexical units the language understands.
 *
 * Produced by Lexer::createToken and consumed by the Parser to decide
 * which grammar rule applies.
 */
enum class tokenType
{
	NUMBER,        ///< Numeric literal: integer or decimal with digits after the point.
	PLUS,          ///< Binary addition or unary plus: "+".
	MINUS,         ///< Binary subtraction or unary negation: "-".
	STAR,          ///< Multiplication: "*".
	SLASH,         ///< Division: "/".
	LPAREN,        ///< Opening parenthesis: "(".
	RPAREN,        ///< Closing parenthesis: ")".
    EQUAL_EQUAL,   ///< Equality: "==". A lone "=" is not part of the language.
    BANG_EQUAL,    ///< Inequality: "!=". A lone "!" is not part of the language.
    LESS,          ///< Comparison: "<".
    LESS_EQUAL,    ///< Comparison: "<=".
    GREATER,       ///< Comparison: ">".
    GREATER_EQUAL, ///< Comparison: ">=".
	EOF_TOKEN,     ///< Sentinel appended after the last real token; its lexeme is empty.

};

/**
 * @brief Returns the identifier of a category as text, for logs and debugging.
 * @param type Category to name.
 * @return The enumerator's own name, e.g. "NUMBER"; "UNKNOWN" if the value
 *         does not match any enumerator.
 */
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
