#include "parser.h"
#include <stdexcept>
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), current(0) {
}

std::unique_ptr<Expr> Parser::parse() {
    return expression();
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
// expression → term (('+' | '-') term)*
std::unique_ptr<Expr> Parser::expression() {
    auto expr = term();

    while (match(tokenType::PLUS) || match(tokenType::MINUS)) {
        Token op = tokens[current - 1];
        auto right = term();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

// term → factor (('*' | '/') factor)*
std::unique_ptr<Expr> Parser::term() {
    auto expr = factor();

    while (match(tokenType::STAR) || match(tokenType::SLASH)) {
        Token op = tokens[current - 1];
        auto right = factor();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::factor() {
    return unary();
}

// factor → unary
std::unique_ptr<Expr> Parser::unary() {
    if (match(tokenType::PLUS) || match(tokenType::MINUS)) {
        Token op = tokens[current - 1];
        auto expr = unary();
        return std::make_unique<Unary>(op, std::move(expr));
    }

    return primary();
}

// primary → NUMBER | '(' expression ')'
std::unique_ptr<Expr> Parser::primary() {
    if (match(tokenType::NUMBER)) {
        double value = std::stod(tokens[current - 1].lexeme);
        return std::make_unique<Literal>(value);
    }

    if (match(tokenType::LPAREN)) {
        auto expr = expression();
        if (!match(tokenType::RPAREN)) {
            throw std::runtime_error("Expected ')' after expression");
        }
        return std::make_unique<Grouping>(std::move(expr));
    }

    throw std::runtime_error("Expected number or '('");
}

void Parser::printAST(Expr* expr, int indent) {
    std::string spaces(indent * 2, ' ');

    if (auto lit = dynamic_cast<Literal*>(expr)) {
        std::cout << spaces << "Literal: " << lit->value << std::endl;
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