#pragma once

#include <sstream>
#include <stdexcept>
#include <string>
#include <variant>

using Value = std::variant<std::monostate, double, bool>;

inline bool isTruthy(const Value& value)
{
    if (std::holds_alternative<std::monostate>(value)) {
        return false;
    }
    if (const auto boolean = std::get_if<bool>(&value)) {
        return *boolean;
    }
    return true;
}

inline double asNumber(const Value& value)
{
    if (const auto number = std::get_if<double>(&value)) {
        return *number;
    }
    throw std::runtime_error("Operand must be a number");
}

inline bool valuesEqual(const Value& left, const Value& right)
{
    return left == right;
}

inline std::string valueToString(const Value& value)
{
    if (std::holds_alternative<std::monostate>(value)) {
        return "nil";
    }
    if (const auto boolean = std::get_if<bool>(&value)) {
        return *boolean ? "true" : "false";
    }

    std::ostringstream output;
    output << std::get<double>(value);
    return output.str();
}
