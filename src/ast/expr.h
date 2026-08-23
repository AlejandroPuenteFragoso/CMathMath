#pragma once
#include "../lexer/token.h"
#include "../runtime/value.h"
#include <memory>
#include <stdexcept>

/**
 * @brief Base node of the expression AST built by the Parser.
 *
 * Every node owns its children through std::unique_ptr, so destroying the
 * root releases the whole tree. Evaluation is a recursive walk started by
 * calling eval() on the root.
 */
struct Expr {
    virtual ~Expr() = default;

    /**
     * @brief Computes the value of this subtree.
     *
     * @return A number, boolean or nil value.
     * @throws std::runtime_error on runtime errors, e.g. division by zero.
     */
    virtual Value eval() = 0;
};

/**
 * @brief Node for a binary operation: arithmetic, comparison or equality.
 *
 * Which operation applies is decided at evaluation time from `op.type`.
 */
struct Binary : Expr {
    std::unique_ptr<Expr> left;  ///< Left operand; evaluated first.
    Token op;                    ///< Operator token; its type selects the operation.
    std::unique_ptr<Expr> right; ///< Right operand.

    Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
        : left(std::move(left)), op(op), right(std::move(right)) {
    }

    /**
     * @brief Evaluates both operands (left first, exactly once each) and applies `op`.
     * @return The arithmetic result, or a boolean for comparisons and equality.
     * @throws std::runtime_error on division by zero, or if `op` is not a
     *         binary operator this node knows how to apply.
     */
    Value eval() override {
        Value leftValue = left->eval();
        Value rightValue = right->eval();
        switch (op.type) {
            case tokenType::PLUS:
                return asNumber(leftValue) + asNumber(rightValue);
            case tokenType::MINUS:
                return asNumber(leftValue) - asNumber(rightValue);
            case tokenType::STAR:
                return asNumber(leftValue) * asNumber(rightValue);
            case tokenType::SLASH: {
                const double divisor = asNumber(rightValue);
                if (divisor == 0.0) {
                    throw std::runtime_error("Division by zero error");
                }
                return asNumber(leftValue) / divisor;
            }
            case tokenType::LESS:
                return asNumber(leftValue) < asNumber(rightValue);

            case tokenType::LESS_EQUAL:
                return asNumber(leftValue) <= asNumber(rightValue);

            case tokenType::GREATER:
                return asNumber(leftValue) > asNumber(rightValue);

            case tokenType::GREATER_EQUAL:
                return asNumber(leftValue) >= asNumber(rightValue);

            case tokenType::EQUAL_EQUAL:
                return valuesEqual(leftValue, rightValue);

            case tokenType::BANG_EQUAL:
                return !valuesEqual(leftValue, rightValue);

            default:
                throw std::runtime_error("Unknown operator");
		}
    }

};

/**
 * @brief Leaf node holding a number, boolean or nil literal.
 */
struct Literal : Expr {
    Value value; ///< The literal's runtime value.
    explicit Literal(Value value) : value(std::move(value)) {}

    /// @return The stored value. Never throws.
    Value eval() override {
        return value;
    }
};

/**
 * @brief Node for a parenthesized expression.
 *
 * Carries no behavior of its own — grouping already shaped the tree during
 * parsing — but preserves the parentheses so tools like printAST can show
 * the source structure faithfully.
 */
struct Grouping : Expr {
    std::unique_ptr<Expr> expression; ///< The expression inside the parentheses.
    explicit Grouping(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {
    }

    /// @return The inner expression's value, unchanged.
    Value eval() override {
        return expression->eval();
    }
};

/**
 * @brief Node for a unary prefix operator applied to one operand.
 *
 * Supports unary plus, numeric negation and logical negation.
 */
struct Unary : Expr {
    Token op;                    ///< Operator token: PLUS, MINUS or BANG.
    std::unique_ptr<Expr> right; ///< Operand the operator applies to.

    Unary(Token op, std::unique_ptr<Expr> right)
        : op(op), right(std::move(right)) {
    }

    /**
     * @brief Evaluates the operand and applies the prefix operator.
     * @return A number for PLUS/MINUS, or a boolean for BANG.
     * @throws std::runtime_error if `op` is not a supported unary operator.
     */
    Value eval() override {
        Value value = right->eval();
        switch (op.type) {
        case tokenType::PLUS:
            return asNumber(value);
        case tokenType::MINUS:
            return -asNumber(value);
        case tokenType::BANG:
            return !isTruthy(value);
        default:
            throw std::runtime_error("Unknown operator");
        }
    }
};
