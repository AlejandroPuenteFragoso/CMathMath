#pragma once
#include "tokentype.h"
#include "token.h"
#include <string>
#include <vector>

class Lexer
{
public:
	Lexer(const std::string& input);

	void advance();
	char peek();
	char peekNext();
	bool isAtEnd();

	void skipWhitespace();
	void scanTokens();
	void scanNumber();
	tokenType createToken(const std::string& value);

	const std::vector<Token>& getTokens() const;

private:
	std::string input;
	size_t current = 0;
	size_t start = 0;
	std::vector<Token> tokens;
};