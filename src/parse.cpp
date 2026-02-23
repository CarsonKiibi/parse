#include <parse.hpp>

Parser::Parser(Lexer lexer) :
    lexer_(std::move(lexer))
    {
        advance();
    }

// parse is entry point to our parse heleprs
// parse helpers return our subtrees
std::unique_ptr<Node> Parser::parse() {

}

void Parser::advance() {
    current_ = lexer_.next();
    
}