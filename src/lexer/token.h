#pragma once
#include "tokenType.h"
#include <string>
#include <cctype>

/**
 * @brief A lexical unit produced by the Lexer.
 *
 * Pairs a token category with the exact source text it was scanned from.
 * Tokens are plain value objects: the Lexer builds them and the Parser
 * only reads them.
 */
class Token
{
public:
    /**
     * @brief Builds a token of the given category.
     * @param type   Category the Parser will dispatch on.
     * @param lexeme Verbatim source text of the token. Empty only for the
     *               EOF_TOKEN sentinel.
     */
    Token(tokenType type, const std::string& lexeme)
        : type(type), lexeme(lexeme) {}

    tokenType type;     ///< Category the Parser dispatches on.
    std::string lexeme; ///< Verbatim source text; for NUMBER it is parseable by std::stod.
};
