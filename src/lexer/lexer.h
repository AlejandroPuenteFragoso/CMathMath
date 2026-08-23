#pragma once
#include "tokenType.h"
#include "token.h"
#include <string>
#include <vector>

/**
 * @brief Converts a source string into the flat list of tokens the Parser consumes.
 *
 * Usage: construct with the input, call scanTokens() exactly once, then read
 * the result with getTokens(). Scanning is eager: the whole input is
 * tokenized in one pass, and any lexical error aborts it with an exception.
 */
class Lexer
{
public:
	/**
	 * @brief Prepares a lexer over the given source text; nothing is scanned yet.
	 * @param input Expression source. The lexer keeps its own copy.
	 */
	Lexer(const std::string& input);

	/// @brief Moves the cursor one character forward and updates its source position.
	void advance();

	/**
	 * @brief Looks at the character under the cursor without consuming it.
	 * @return The current character, or '\0' when the cursor is past the end.
	 */
	char peek();

	/**
	 * @brief Looks one character beyond the cursor without consuming anything.
	 * @return The next character, or '\0' when it would fall past the end.
	 */
	char peekNext();

	/// @return true once the cursor has consumed the entire input.
	bool isAtEnd();

	/// @brief Advances the cursor past any run of whitespace (spaces, tabs, newlines).
	void skipWhitespace();

	/**
	 * @brief Tokenizes the entire input and stores the result.
	 *
	 * Recognizes numeric and logical literals, arithmetic operators, parentheses and the
	 * comparison/equality operators, including the two-character forms
	 * ("==", "!=", "<=", ">="). Always appends a final EOF_TOKEN sentinel.
	 * Call it once per Lexer: a second call would append a duplicate stream.
	 *
	 * @throws std::runtime_error if the input contains a malformed number or
	 *         any character or word outside the language (a lone '=' included).
	 */
	void scanTokens();

	/**
	 * @brief Scans one numeric literal and appends its NUMBER token.
	 *
	 * Precondition: the character under the cursor is a digit and `start`
	 * marks where the literal begins. Accepts integers and decimals; a
	 * decimal point must be followed by at least one digit.
	 *
	 * @throws std::runtime_error on malformed literals such as "3." or "1.2.3".
	 */
	void scanNumber();

	/**
	 * @brief Scans a keyword (`true`, `false` or `nil`) and appends its token.
	 * @throws std::runtime_error when the scanned word is not a language keyword.
	 */
	void scanIdentifier();

	/**
	 * @brief Classifies an operator or parenthesis lexeme.
	 * @param value Lexeme to classify, e.g. "+", "(", "<=", "true".
	 * @return The matching category; NUMBER when the lexeme is a numeric string.
	 * @throws std::runtime_error ("Unexpected character: ...") when the lexeme
	 *         is not part of the language. This is what rejects invalid input
	 *         instead of silently truncating it.
	 */
	tokenType createToken(const std::string& value);

	/**
	 * @return The tokens produced by scanTokens(), ending in EOF_TOKEN.
	 *         Empty if scanTokens() has not run yet.
	 */
	const std::vector<Token>& getTokens() const;

private:
	std::string input;         ///< Full source text being scanned.
	size_t current = 0;        ///< Cursor: index of the next character to consume.
	size_t start = 0;          ///< Index where the lexeme in progress begins.
	int currentLine = 1;       ///< Line containing the next character to consume.
	int currentColumn = 1;     ///< Column containing the next character to consume.
	int startLine = 1;         ///< Line where the lexeme in progress begins.
	int startColumn = 1;       ///< Column where the lexeme in progress begins.
	std::vector<Token> tokens; ///< Output, filled by scanTokens().
};
