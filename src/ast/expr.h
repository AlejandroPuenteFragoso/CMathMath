#pragma once
#include "../lexer/token.h"
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
     * Every value in the language is a double for now; comparisons yield
     * 1.0 (true) or 0.0 (false) until a boolean type exists (issue #16).
     *
     * @return The numeric result of the subtree.
     * @throws std::runtime_error on runtime errors, e.g. division by zero.
     */
    virtual double eval()= 0;
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
     * @return The arithmetic result, or 1.0/0.0 for comparisons and equality.
     * @throws std::runtime_error on division by zero, or if `op` is not a
     *         binary operator this node knows how to apply.
     */
    double eval() override {
        double leftValue = left->eval();
        double rightValue = right->eval();
        switch (op.type) {
            case tokenType::PLUS:
                return leftValue + rightValue;
            case tokenType::MINUS:
                return leftValue - rightValue;
            case tokenType::STAR:
                return leftValue * rightValue;
            case tokenType::SLASH:
                if (rightValue == 0.0) {
                    throw std::runtime_error("Division by zero error");
                }
                return leftValue / rightValue;
            case tokenType::LESS:
                return leftValue < rightValue ? 1.0 : 0.0;

            case tokenType::LESS_EQUAL:
                return leftValue <= rightValue ? 1.0 : 0.0;

            case tokenType::GREATER:
                return leftValue > rightValue ? 1.0 : 0.0;

            case tokenType::GREATER_EQUAL:
                return leftValue >= rightValue ? 1.0 : 0.0;

            case tokenType::EQUAL_EQUAL:
                return leftValue == rightValue ? 1.0 : 0.0;

            case tokenType::BANG_EQUAL:
                return leftValue != rightValue ? 1.0 : 0.0;

            default:
                throw std::runtime_error("Operador desconocido");
		}
    }

};

/**
 * @brief Leaf node holding a numeric literal, already parsed to double.
 */
struct Literal : Expr {
    double value; ///< The literal's value, converted by the Parser with std::stod.
    explicit Literal(double value) : value(value) {}

    /// @return The stored value. Never throws.
    double eval() override {
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
    double eval() override {
        return expression->eval();
    }
};

/**
 * @brief Node for a unary prefix operator applied to one operand.
 *
 * Only unary plus and minus exist today; logical not ("!") arrives with
 * issue #16.
 */
struct Unary : Expr {
    Token op;                    ///< Operator token: PLUS or MINUS.
    std::unique_ptr<Expr> right; ///< Operand the operator applies to.

    Unary(Token op, std::unique_ptr<Expr> right)
        : op(op), right(std::move(right)) {
    }

    /**
     * @brief Evaluates the operand and applies the prefix operator.
     * @return The operand's value, negated when `op` is MINUS.
     * @throws std::runtime_error if `op` is not a supported unary operator.
     */
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
