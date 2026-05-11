#pragma once
#include "tokentype.h"
#include <string>
class Lexer
{
public:
	Lexer(const std::string& input);

	void advance();

	char peek();

	bool isAtEnd();



	void skipWhitespace();

	void scanTokens();

	tokenType createToken(const std::string& value);



private:
		std::string input;
		size_t current = 0;
};
