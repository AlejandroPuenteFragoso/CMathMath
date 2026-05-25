#include <iostream>
#include <string>
#include <iomanip>
#include "../lexer/lexer.h"
#include "../lexer/tokenType.h"

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
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}