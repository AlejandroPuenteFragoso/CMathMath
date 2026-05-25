#pragma once
#include "../lexer/token.h"
#include <memory>

struct Expr {
    virtual ~Expr() = default;
};

struct Binary : Expr {
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

    Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
        : left(std::move(left)), op(op), right(std::move(right)) {
    }
};

struct Literal : Expr {
    double value;
    explicit Literal(double value) : value(value) {}
};

struct Grouping : Expr {
    std::unique_ptr<Expr> expression;
    explicit Grouping(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {
    }
};

struct Unary : Expr {
    Token op;
    std::unique_ptr<Expr> right;

    Unary(Token op, std::unique_ptr<Expr> right)
        : op(op), right(std::move(right)) {
    }
};