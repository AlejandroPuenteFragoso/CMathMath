#include "astPrinter.h"

#include <ostream>
#include <string>

AstPrinter::AstPrinter(std::ostream& output) : output(output) {}

void AstPrinter::print(Expr& expr) {
    indent = 0;
    expr.accept(*this);
}

void AstPrinter::printChild(Expr& expr) {
    ++indent;
    expr.accept(*this);
    --indent;
}

void AstPrinter::printIndent() {
    output << std::string(indent * 2, ' ');
}

void AstPrinter::visitBinary(Binary& expr) {
    printIndent();
    output << "Binary: " << expr.op.lexeme << std::endl;
    printChild(*expr.left);
    printChild(*expr.right);
}

void AstPrinter::visitGrouping(Grouping& expr) {
    printIndent();
    output << "Grouping" << std::endl;
    printChild(*expr.expression);
}

void AstPrinter::visitLiteral(Literal& expr) {
    printIndent();
    output << "Literal: " << valueToString(expr.value) << std::endl;
}

void AstPrinter::visitUnary(Unary& expr) {
    printIndent();
    output << "Unary: " << expr.op.lexeme << std::endl;
    printChild(*expr.right);
}
