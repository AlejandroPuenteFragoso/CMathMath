#include <iostream>
#include <string>
#include <iomanip>
#include "../lexer/lexer.h"
#include "../lexer/tokenType.h"
#include "../parser/parser.h"

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
            auto result = ast->eval();

            std::cout << "AST created successfully\n";
            parser.printAST(ast.get());
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
