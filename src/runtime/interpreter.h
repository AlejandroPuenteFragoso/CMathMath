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
     * @throws std::runtime_error if a numeric operator receives a boolean or
     *         nil operand, division uses a zero divisor, or an operator is
     *         unsupported. Equality accepts all Value types, and logical
     *         negation uses truthiness rather than numeric conversion.
     */
    Value evaluate(Expr& expr);

private:
    /**
     * @brief Evaluates arithmetic, order comparison or equality.
     * @throws std::runtime_error if an arithmetic or order comparison operand
     *         is not a number, the divisor is zero, or the operator is
     *         unsupported. Equality accepts numbers, booleans and nil.
     */
    void visitBinary(Binary& expr) override;
    void visitGrouping(Grouping& expr) override;
    void visitLiteral(Literal& expr) override;
    /**
     * @brief Evaluates numeric unary operations or logical negation.
     * @throws std::runtime_error if unary plus or minus receives a boolean or
     *         nil operand, or the operator is unsupported. Logical negation
     *         accepts every Value type.
     */
    void visitUnary(Unary& expr) override;

    Value eval(Expr& expr);
    Value result;
};
