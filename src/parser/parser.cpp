#include "parser.h"
#include <stdexcept>
#include <iostream>

namespace {

std::string describeToken(const Token& token)
{
    if (token.type == tokenType::EOF_TOKEN) {
        return "<end of input>";
    }
    return "'" + token.lexeme + "'";
}

bool isEqualityOperator(tokenType type)
{
    return type == tokenType::EQUAL_EQUAL || type == tokenType::BANG_EQUAL;
}

bool isComparisonOperator(tokenType type)
{
    return type == tokenType::LESS ||
           type == tokenType::LESS_EQUAL ||
           type == tokenType::GREATER ||
           type == tokenType::GREATER_EQUAL;
}

[[noreturn]] void throwParserError(const Token& token, const std::string& message)
{
    throw std::runtime_error(
        "Error [line " + std::to_string(token.line) +
        ", column " + std::to_string(token.column) + "]: " + message
    );
}

} // namespace

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), current(0) {
}

std::unique_ptr<Expr> Parser::parse() {
    auto expr = expression();
    if (!isAtEnd() || peek().type != tokenType::EOF_TOKEN) {
        Token token = peek();
        throwParserError(
            token,
            "Unexpected token " + describeToken(token) + " after expression"
        );
    }
    return expr;
}

Token Parser::peek() {
    if (isAtEnd()) {
        return tokens.back();  // Return EOF_TOKEN
    }
    return tokens[current];
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return tokens[current - 1];
}

bool Parser::isAtEnd() {
    return current >= tokens.size() || tokens[current].type == tokenType::EOF_TOKEN;
}

bool Parser::check(tokenType type) {
    if (isAtEnd()) return false;
    return peek().type == type;
}

bool Parser::match(tokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

// Grammar:
// expression -> equality
std::unique_ptr<Expr> Parser::expression() {
    return equality();
}

// factor → unary (("*" | "/") unary)*
std::unique_ptr<Expr> Parser::factor() {
    auto expr = unary();

    while (match(tokenType::STAR) || match(tokenType::SLASH)) {
        Token op = tokens[current - 1];
        auto right = unary();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

// unary → ("!" | "+" | "-") unary | primary
std::unique_ptr<Expr> Parser::unary() {
    if (match(tokenType::BANG) || match(tokenType::PLUS) || match(tokenType::MINUS)) {
        Token op = tokens[current - 1];
        auto expr = unary();
        return std::make_unique<Unary>(op, std::move(expr));
    }

    return primary();
}

// primary → NUMBER | "true" | "false" | "nil" | '(' expression ')'
std::unique_ptr<Expr> Parser::primary() {
    if (match(tokenType::FALSE)) {
        return std::make_unique<Literal>(false);
    }

    if (match(tokenType::TRUE)) {
        return std::make_unique<Literal>(true);
    }

    if (match(tokenType::NIL)) {
        return std::make_unique<Literal>(std::monostate{});
    }

    if (match(tokenType::NUMBER)) {
        double value = std::stod(tokens[current - 1].lexeme);
        return std::make_unique<Literal>(value);
    }

    if (match(tokenType::LPAREN)) {
        auto expr = expression();
        if (!match(tokenType::RPAREN)) {
            throwParserError(peek(), "Expected ')' after expression");
        }
        return std::make_unique<Grouping>(std::move(expr));
    }

    Token token = peek();
    throwParserError(
        token,
        "Expected expression, found " + describeToken(token)
    );
}

// equality -> comparison (("==" | "!=") comparison)?
std::unique_ptr<Expr> Parser::equality() {
    auto expr = comparison();

    if (isEqualityOperator(peek().type)) {
        Token op = advance();
        auto right = comparison();
        expr = std::make_unique<Binary>(
            std::move(expr),
            op,
            std::move(right)
        );
    }

    if (isEqualityOperator(peek().type)) {
        throwParserError(peek(), "Chained comparisons are not supported");
    }

    return expr;
}

// comparison -> term ((">" | ">=" | "<" | "<=") term)?
std::unique_ptr<Expr> Parser::comparison() {
    auto expr = term();

    if (isComparisonOperator(peek().type)) {
        Token op = advance();
        auto right = term();

        expr = std::make_unique<Binary>(
            std::move(expr),
            op,
            std::move(right)
        );
    }

    if (isComparisonOperator(peek().type)) {
        throwParserError(peek(), "Chained comparisons are not supported");
    }

    return expr;
}

// term -> factor (("+" | "-") factor)*
std::unique_ptr<Expr> Parser::term() {
    auto expr = factor();

    while (match(tokenType::PLUS) || match(tokenType::MINUS)) {
        Token op = tokens[current - 1];
        auto right = factor();

        expr = std::make_unique<Binary>(
            std::move(expr),
            op,
            std::move(right)
        );
    }

    return expr;
}

void Parser::printAST(Expr* expr, int indent) {
    std::string spaces(indent * 2, ' ');

    if (auto lit = dynamic_cast<Literal*>(expr)) {
        std::cout << spaces << "Literal: " << valueToString(lit->value) << std::endl;
    }
    else if (auto unary = dynamic_cast<Unary*>(expr)) {
        std::cout << spaces << "Unary: " << unary->op.lexeme << std::endl;
        printAST(unary->right.get(), indent + 1);
    }
    else if (auto binary = dynamic_cast<Binary*>(expr)) {
        std::cout << spaces << "Binary: " << binary->op.lexeme << std::endl;
        printAST(binary->left.get(), indent + 1);
        printAST(binary->right.get(), indent + 1);
    }
    else if (auto group = dynamic_cast<Grouping*>(expr)) {
        std::cout << spaces << "Grouping" << std::endl;
        printAST(group->expression.get(), indent + 1);
    }
}
