#pragma once

#include "../ast/expr.h"

/**
 * @brief Evaluates expression trees and owns their runtime semantics.
 *
 * The last visited value is kept as visitor state. evaluate() is the public
 * entry point; recursive visits use eval() to retrieve each child value.
 */
class Interpreter final : public ExprVisitor {
public:
    /**
     * @brief Evaluates an expression tree.
     * @return A number, boolean or nil value.
     * @throws std::runtime_error on runtime errors.
     */
    Value evaluate(Expr& expr);

private:
    void visitBinary(Binary& expr) override;
    void visitGrouping(Grouping& expr) override;
    void visitLiteral(Literal& expr) override;
    void visitUnary(Unary& expr) override;

    Value eval(Expr& expr);
    Value result;
};
