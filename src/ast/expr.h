#pragma once
#include "../lexer/token.h"
#include <memory>
#include <stdexcept>

struct Expr {
    virtual ~Expr() = default;
    virtual double eval()= 0;
};

struct Binary : Expr {
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

    Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
        : left(std::move(left)), op(op), right(std::move(right)) {
    }

    double eval() override {
        switch (op.type) {
            case tokenType::PLUS:
                return left->eval() + right->eval();
            case tokenType::MINUS:
                return left->eval() - right->eval();
            case tokenType::STAR:
                return left->eval() * right->eval();
            case tokenType::SLASH:
                if (right->eval() == 0.0) {
                    throw std::runtime_error("Division by zero error");
                }
                return left->eval() / right->eval();
            default:
                throw std::runtime_error("Operador desconocido");
		}
    }

};

struct Literal : Expr {
    double value;
    explicit Literal(double value) : value(value) {}
    double eval() override {
        return value;
    }
};

struct Grouping : Expr {
    std::unique_ptr<Expr> expression;
    explicit Grouping(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {
    }
    double eval() override {
        return expression->eval();
    }
};

struct Unary : Expr {
    Token op;
    std::unique_ptr<Expr> right;

    Unary(Token op, std::unique_ptr<Expr> right)
        : op(op), right(std::move(right)) {
    }
    double eval() override {
        switch (op.type) {
        case tokenType::PLUS:
            return right->eval();
        case tokenType::MINUS:
            return -right->eval();
        default:
            throw std::runtime_error("Operador desconocido");
        }
    }
};