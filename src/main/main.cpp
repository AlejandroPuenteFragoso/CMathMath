#include <iostream>
#include <string>
#include <iomanip>
#include "../lexer/lexer.h"
#include "../lexer/tokenType.h"
#include "../parser/parser.h"
#include "../runtime/interpreter.h"
#include "../ast/astPrinter.h"

int main() {
    std::string input;

    while (true) {
        std::cout << "\nInput: ";
        if (!std::getline(std::cin, input)) {
            std::cout << "Bye!\n";
            break;
        }

        if (input == "exit") {
            std::cout << "Bye!\n";
            break;
        }

        if (input.empty()) {
            continue;
        }

        try {
            Lexer lexer(input);
            lexer.scanTokens();

            std::cout << "\nTokens found:\n";
            std::cout << "------------------\n";

            for (const auto& token : lexer.getTokens()) {
                std::cout << std::left << std::setw(15)
                    << tokenTypeToString(token.type)
                    << " -> '" << token.lexeme << "'"
                    << " [line " << token.line
                    << ", column " << token.column << "]\n";
            }

            std::cout << "------------------\n";

            Parser parser(lexer.getTokens());
            auto ast = parser.parse();
            Interpreter interpreter;
            auto result = interpreter.evaluate(*ast);

            std::cout << "AST created successfully\n";
            AstPrinter printer(std::cout);
            printer.print(*ast);
            std::cout << "Result: " << valueToString(result) << "\n";
        }
        catch (const std::exception& e) {
            std::string message = e.what();
            if (message.rfind("Error [", 0) == 0) {
                std::cout << message << "\n";
            } else {
                std::cout << "Error: " << message << "\n";
            }
        }
    }

    return 0;
}
