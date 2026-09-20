#pragma once

#include "expr.h"
#include <iosfwd>

/**
 * @brief Prints the structure of an expression tree for debugging.
 *
 * Two spaces are written for each level. The printer has no parser duties
 * and can write to any output stream.
 */
class AstPrinter final : public ExprVisitor {
public:
    explicit AstPrinter(std::ostream& output);

    /// @brief Prints the tree rooted at expr and resets indentation.
    void print(Expr& expr);

private:
    void visitBinary(Binary& expr) override;
    void visitGrouping(Grouping& expr) override;
    void visitLiteral(Literal& expr) override;
    void visitUnary(Unary& expr) override;

    void printChild(Expr& expr);
    void printIndent();

    std::ostream& output;
    int indent = 0;
};
