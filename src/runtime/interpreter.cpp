#include "interpreter.h"

#include <stdexcept>
#include <utility>

namespace {

using NumericOperation = Value (*)(double, double);

struct NumericOperator {
    tokenType type;
    NumericOperation operation;
};

const NumericOperator numericOperators[] = {
    {tokenType::PLUS, [](double a, double b) -> Value { return a + b; }},
    {tokenType::MINUS, [](double a, double b) -> Value { return a - b; }},
    {tokenType::STAR, [](double a, double b) -> Value { return a * b; }},
    {tokenType::SLASH, [](double a, double b) -> Value { return a / b; }},
    {tokenType::LESS, [](double a, double b) -> Value { return a < b; }},
    {tokenType::LESS_EQUAL, [](double a, double b) -> Value { return a <= b; }},
    {tokenType::GREATER, [](double a, double b) -> Value { return a > b; }},
    {tokenType::GREATER_EQUAL, [](double a, double b) -> Value { return a >= b; }}
};

const NumericOperator* findNumericOperator(tokenType type) {
    for (const auto& op : numericOperators) {
        if (op.type == type) {
            return &op;
        }
    }
    return nullptr;
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
    const NumericOperator* op = findNumericOperator(expr.op.type);

if (op == nullptr) {
    throw std::runtime_error("Unknown operator");
}

const auto [leftNumber, rightNumber] =
    checkNumberOperands(leftValue, rightValue);

if (expr.op.type == tokenType::SLASH && rightNumber == 0.0) {
    throw std::runtime_error("Division by zero error");
}

result = op->operation(leftNumber, rightNumber);
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
