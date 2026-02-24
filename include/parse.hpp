#include <memory>
#include <ast.hpp>
#include <lexer.hpp>
#include <stack>

class Parser {
    public:
        explicit Parser(Lexer lexer);
        std::unique_ptr<Node> parse();

    private:
        // recursive descent parsing methods
        std::unique_ptr<Node> parseExpr();   // for + and -
        std::unique_ptr<Node> parseTerm();   // for * and /
        std::unique_ptr<Node> parseFactor(); // for unary -, parens, numbers

        // get next token from lexer and decide what current token is
        void advance();

        // check if current token matches expected type
        bool check(TokenType type) const;

        // consume token if it matches expected type
        bool match(TokenType type);

        // except a token type or throw err
        void expect(TokenType type, const std::string& message);

        Lexer lexer_;
        Token current_;
};