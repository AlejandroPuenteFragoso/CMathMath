#include <doctest/doctest.h>
#include <sstream>
#include <string>
#include "ast/astPrinter.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

TEST_CASE("AstPrinter: preserves the existing tree output") {
    Lexer lexer("!(1 + 2) == false");
    lexer.scanTokens();
    Parser parser(lexer.getTokens());
    auto ast = parser.parse();

    std::ostringstream output;
    AstPrinter printer(output);
    printer.print(*ast);

    CHECK(output.str() ==
        "Binary: ==\n"
        "  Unary: !\n"
        "    Grouping\n"
        "      Binary: +\n"
        "        Literal: 1\n"
        "        Literal: 2\n"
        "  Literal: false\n");
}
