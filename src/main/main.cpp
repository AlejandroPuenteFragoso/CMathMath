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
            std::cout << "¡Bye!\n";
            break;
        }

        if (input == "exit") {
            std::cout << "¡Bye!\n";
            break;
        }

        if (input.empty()) {
            continue;
        }

        try {
            Lexer lexer(input);
            lexer.scanTokens();

            std::cout << "\nTokens encontrados:\n";
            std::cout << "------------------\n";

            for (const auto& token : lexer.getTokens()) {
                std::cout << std::left << std::setw(15)
                    << tokenTypeToString(token.type)
                    << " -> '" << token.lexeme << "'\n";
            }

            std::cout << "------------------\n";

            Parser parser(lexer.getTokens());
            auto ast = parser.parse();

            std::cout << "AST creado exitosamente\n";
			parser.printAST(ast.get());
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}