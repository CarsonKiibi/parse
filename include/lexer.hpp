#pragma once

#include <string>

enum class TokenType {
    Number,
    Plus,
    Minus,
    Multiply,
    Divide,
    Power,
    LParen,
    RParen,
    End
};

struct Token {
    TokenType type;
    std::string text;
};


class Lexer {
public:
    explicit Lexer(std::string input);
    Token next();

private:
    std::string input_;
    size_t pos_;

    void skipWhitespace();
    Token readNumber();
};