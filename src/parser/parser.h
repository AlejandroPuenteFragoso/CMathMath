#pragma once
#include "../lexer/token.h"
#include "../ast/expr.h"
#include <vector>
#include <memory>

/**
 * @brief Recursive-descent parser that turns a token list into an AST.
 *
 * Each private method implements one rule of the grammar (docs/grammar.md),
 * from lowest to highest precedence:
 *
 *   expression -> equality
 *   equality   -> comparison (("==" | "!=") comparison)*
 *   comparison -> additive ((">" | ">=" | "<" | "<=") additive)*
 *   additive   -> term (("+" | "-") term)*
 *   term       -> factor (("*" | "/") factor)*
 *   factor     -> unary
 *   unary      -> ("+" | "-") unary | primary
 *   primary    -> NUMBER | "(" expression ")"
 *
 * The input must come from Lexer::getTokens(), so it always ends with an
 * EOF_TOKEN sentinel.
 */
class Parser {
public:
    /**
     * @brief Prepares a parser over a token stream; nothing is parsed yet.
     * @param tokens Token list ending in EOF_TOKEN. The parser keeps a copy.
     */
    explicit Parser(const std::vector<Token>& tokens);

    /**
     * @brief Parses the whole token stream as a single expression.
     * @return Root of the resulting AST; evaluate it with Expr::eval().
     * @throws std::runtime_error if the stream is not one well-formed
     *         expression: unexpected token, missing ')' or trailing tokens
     *         after the expression (e.g. "1 2").
     */
    std::unique_ptr<Expr> parse();

    /**
     * @brief Prints the tree shape of an AST to stdout, for debugging.
     * @param expr   Root of the subtree to print. Must not be null.
     * @param indent Depth of the current node; two spaces per level.
     */
    void printAST(Expr* expr, int indent = 0);

private:
    std::vector<Token> tokens; ///< Input stream, always terminated by EOF_TOKEN.
    size_t current = 0;        ///< Index of the next token to consume.

    /// @brief expression -> equality. Entry rule, lowest precedence.
    std::unique_ptr<Expr> expression();
    /// @brief term -> factor (("*" | "/") factor)*. Left-associative.
    std::unique_ptr<Expr> term();
    /// @brief factor -> unary. Passthrough level (see issue #27).
    std::unique_ptr<Expr> factor();
    /// @brief unary -> ("+" | "-") unary | primary. Right-associative by recursion.
    std::unique_ptr<Expr> unary();
    /**
     * @brief primary -> NUMBER | "(" expression ")". Highest precedence.
     * @throws std::runtime_error on any other token, or if the ')' is missing.
     */
    std::unique_ptr<Expr> primary();
    /**
     * @brief equality -> comparison (("==" | "!=") comparison)*. Left-associative:
     *        chains like "a == b == c" parse as "(a == b) == c" (see issue #39).
     */
    std::unique_ptr<Expr> equality();
    /// @brief comparison -> additive ((">" | ">=" | "<" | "<=") additive)*. Left-associative.
    std::unique_ptr<Expr> comparison();
    /// @brief additive -> term (("+" | "-") term)*. Left-associative.
    std::unique_ptr<Expr> additive();

    /// @brief Consumes the current token. @return The token just consumed.
    Token advance();
    /// @return The current token without consuming it; EOF_TOKEN at the end.
    Token peek();
    /// @return true when the current token is EOF_TOKEN (or the stream ran out).
    bool isAtEnd();
    /// @return true if the current token is of the given type. Consumes nothing.
    bool check(tokenType type);
    /**
     * @brief Consumes the current token only if it matches the given type.
     * @return true if it matched and was consumed; false leaves the cursor untouched.
     */
    bool match(tokenType type);
};
