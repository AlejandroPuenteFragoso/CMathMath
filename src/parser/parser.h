#pragma once
#include "../lexer/token.h"
#include "../ast/expr.h"
#include <vector>
#include <memory>

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    std::unique_ptr<Expr> parse();
    void printAST(Expr* expr, int indent = 0);

private:
    std::vector<Token> tokens;
    size_t current = 0;

    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> term();
    std::unique_ptr<Expr> factor();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();
    Token advance();
    Token peek();
    bool isAtEnd();
    bool check(tokenType type);
    bool match(tokenType type);
};