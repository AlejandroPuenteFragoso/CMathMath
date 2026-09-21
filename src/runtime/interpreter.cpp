#include "interpreter.h"

#include <stdexcept>
#include <utility>

namespace {

bool isNumericOperator(tokenType type) {
    switch (type) {
    case tokenType::PLUS:
    case tokenType::MINUS:
    case tokenType::STAR:
    case tokenType::SLASH:
    case tokenType::LESS:
    case tokenType::LESS_EQUAL:
    case tokenType::GREATER:
    case tokenType::GREATER_EQUAL:
        return true;
    default:
        return false;
    }
}

std::pair<double, double> checkNumberOperands(const Value& left, const Value& right) {
    const double leftNumber = asNumber(left);
    const double rightNumber = asNumber(right);
    return {leftNumber, rightNumber};
}

} // namespace

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

    if (expr.op.type == tokenType::EQUAL_EQUAL) {
        result = valuesEqual(leftValue, rightValue);
        return;
    }
    if (expr.op.type == tokenType::BANG_EQUAL) {
        result = !valuesEqual(leftValue, rightValue);
        return;
    }
    if (!isNumericOperator(expr.op.type)) {
        throw std::runtime_error("Unknown operator");
    }

    const auto [leftNumber, rightNumber] = checkNumberOperands(leftValue, rightValue);

    switch (expr.op.type) {
    case tokenType::PLUS:
        result = leftNumber + rightNumber;
        break;
    case tokenType::MINUS:
        result = leftNumber - rightNumber;
        break;
    case tokenType::STAR:
        result = leftNumber * rightNumber;
        break;
    case tokenType::SLASH: {
        if (rightNumber == 0.0) {
            throw std::runtime_error("Division by zero error");
        }
        result = leftNumber / rightNumber;
        break;
    }
    case tokenType::LESS:
        result = leftNumber < rightNumber;
        break;
    case tokenType::LESS_EQUAL:
        result = leftNumber <= rightNumber;
        break;
    case tokenType::GREATER:
        result = leftNumber > rightNumber;
        break;
    case tokenType::GREATER_EQUAL:
        result = leftNumber >= rightNumber;
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
