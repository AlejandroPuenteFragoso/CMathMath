#include "interpreter.h"

#include <stdexcept>

Value Interpreter::evaluate(Expr& expr) {
    return eval(expr);
}

Value Interpreter::eval(Expr& expr) {
    expr.accept(*this);
    return result;
}

void Interpreter::visitBinary(Binary& expr) {
    Value leftValue = eval(*expr.left);
    Value rightValue = eval(*expr.right);

    switch (expr.op.type) {
    case tokenType::PLUS:
        result = asNumber(leftValue) + asNumber(rightValue);
        break;
    case tokenType::MINUS:
        result = asNumber(leftValue) - asNumber(rightValue);
        break;
    case tokenType::STAR:
        result = asNumber(leftValue) * asNumber(rightValue);
        break;
    case tokenType::SLASH: {
        const double divisor = asNumber(rightValue);
        if (divisor == 0.0) {
            throw std::runtime_error("Division by zero error");
        }
        result = asNumber(leftValue) / divisor;
        break;
    }
    case tokenType::LESS:
        result = asNumber(leftValue) < asNumber(rightValue);
        break;
    case tokenType::LESS_EQUAL:
        result = asNumber(leftValue) <= asNumber(rightValue);
        break;
    case tokenType::GREATER:
        result = asNumber(leftValue) > asNumber(rightValue);
        break;
    case tokenType::GREATER_EQUAL:
        result = asNumber(leftValue) >= asNumber(rightValue);
        break;
    case tokenType::EQUAL_EQUAL:
        result = valuesEqual(leftValue, rightValue);
        break;
    case tokenType::BANG_EQUAL:
        result = !valuesEqual(leftValue, rightValue);
        break;
    default:
        throw std::runtime_error("Unknown operator");
    }
}

void Interpreter::visitGrouping(Grouping& expr) {
    result = eval(*expr.expression);
}

void Interpreter::visitLiteral(Literal& expr) {
    result = expr.value;
}

void Interpreter::visitUnary(Unary& expr) {
    Value value = eval(*expr.right);

    switch (expr.op.type) {
    case tokenType::PLUS:
        result = asNumber(value);
        break;
    case tokenType::MINUS:
        result = -asNumber(value);
        break;
    case tokenType::BANG:
        result = !isTruthy(value);
        break;
    default:
        throw std::runtime_error("Unknown operator");
    }
}
