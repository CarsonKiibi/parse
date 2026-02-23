#include <memory>
#include <ast.hpp>
#include <lexer.hpp>

class Parser {
    public:
        explicit Parser(Lexer lexer);
        std::unique_ptr<Node> parse();

    private:
        // get next token from lexer and decide what current token is
        void advance();

        Lexer lexer_;
        Token current_;
};