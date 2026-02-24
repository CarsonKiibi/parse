#include <iostream>
#include <lexer.hpp>
#include <parse.hpp>
#include <string>

int main() {
    std::string expressions[] = {
        "5 + 3",
        "10 - 4",
        "2 * 6",
        "15 / 3",
        "2 + 3 * 4",
        "(2 + 3) * 4",
        "10 - 2 * 3",
        "-5 + 3",
        "-(5 + 3)",
        "5.5 + 2.3",
        "3.14 * 2",
        "10 / 4",
        "(1 + 2) * (3 + 4)",
        "-3 * -4",
        "2 + -5",
        "((2 + 3) * 4) / 5"
    };

    for (const auto& expr : expressions) {
        try {
            Lexer lexer(expr);
            Parser parser(std::move(lexer));
            auto ast = parser.parse();
            double result = ast->eval();
            std::cout << expr << " = " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << expr << " -> Error: " << e.what() << "\n";
        }
    }

    return 0;
}