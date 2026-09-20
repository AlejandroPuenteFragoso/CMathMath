#pragma once

#include "../lexer/token.h"
#include "../runtime/value.h"
#include <memory>
#include <utility>

struct Binary;
struct Grouping;
struct Literal;
struct Unary;

/**
 * @brief Operation over every expression node in the AST.
 *
 * Each concrete operation owns its own state. Expression nodes only store
 * syntax and dispatch to the matching visit method.
 */
struct ExprVisitor {
    virtual ~ExprVisitor() = default;
    virtual void visitBinary(Binary& expr) = 0;
    virtual void visitGrouping(Grouping& expr) = 0;
    virtual void visitLiteral(Literal& expr) = 0;
    virtual void visitUnary(Unary& expr) = 0;
};

/**
 * @brief Base node of the expression AST built by the Parser.
 *
 * Every node owns its children through std::unique_ptr, so destroying the
 * root releases the whole tree. Operations are implemented by visitors.
 */
struct Expr {
    virtual ~Expr() = default;

    /// @brief Dispatches this node to the corresponding visitor operation.
    virtual void accept(ExprVisitor& visitor) = 0;
};

/**
 * @brief Node for a binary operation: arithmetic, comparison or equality.
 */
struct Binary : Expr {
    std::unique_ptr<Expr> left;  ///< Left operand.
    Token op;                    ///< Operator token; its type selects the operation.
    std::unique_ptr<Expr> right; ///< Right operand.

    Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
        : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

    void accept(ExprVisitor& visitor) override { visitor.visitBinary(*this); }
};

/**
 * @brief Leaf node holding a number, boolean or nil literal.
 */
struct Literal : Expr {
    Value value; ///< The literal's runtime value.

    explicit Literal(Value value) : value(std::move(value)) {}

    void accept(ExprVisitor& visitor) override { visitor.visitLiteral(*this); }
};

/**
 * @brief Node for a parenthesized expression.
 *
 * Grouping preserves the source structure for operations such as AstPrinter.
 */
struct Grouping : Expr {
    std::unique_ptr<Expr> expression; ///< Expression inside the parentheses.

    explicit Grouping(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {}

    void accept(ExprVisitor& visitor) override { visitor.visitGrouping(*this); }
};

/**
 * @brief Node for a unary prefix operator applied to one operand.
 */
struct Unary : Expr {
    Token op;                    ///< Operator token: PLUS, MINUS or BANG.
    std::unique_ptr<Expr> right; ///< Operand the operator applies to.

    Unary(Token op, std::unique_ptr<Expr> right)
        : op(std::move(op)), right(std::move(right)) {}

    void accept(ExprVisitor& visitor) override { visitor.visitUnary(*this); }
};
