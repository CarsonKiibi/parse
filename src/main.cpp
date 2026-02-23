#include <iostream>
#include <lexer.hpp>

int main() {
    Lexer lexer("         5.123 + 7      二二   *      (4 //// 2)");
    while (true) {
        Token token = lexer.next();
        if (token.type == TokenType::End) break;

        std::cout << "Token: " << token.text << "\n";
    }
}