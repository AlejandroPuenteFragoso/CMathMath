#pragma once
#include "tokenType.h"
#include <string>
#include <cctype>

class Token
{
public:
    Token(tokenType type, const std::string& lexeme)
        : type(type), lexeme(lexeme) {}

    tokenType type;
    std::string lexeme;

   
};
