#include <cctype>
#include <stdexcept>
#include <lexer.hpp>
#include <utility>

Lexer::Lexer(std::string input)
    : input_(std::move(input)), pos_(0) {}

Token Lexer::next() {
    skipWhitespace();

    if (pos_ >= input_.size()) {
        return {TokenType::End, ""};
    }

    char c = input_[pos_];

    if (std::isdigit(c) || c == '.') {
        return readNumber(); 
    }

    ++pos_;

    switch (c) {
        case '+': return {TokenType::Plus, "+"};
        case '-': return {TokenType::Minus, "-"};
        case '*': return {TokenType::Multiply, "*"};
        case '/': return {TokenType::Divide, "/"};
        case '^': return {TokenType::Power, "^"};
        case '(': return {TokenType::LParen, "("};
        case ')': return {TokenType::RParen, ")"};
    }

    throw std::runtime_error("Error: unidentified token");
}

void Lexer::skipWhitespace() {
    while (pos_ < input_.size() &&
           std::isspace(static_cast<unsigned char>(input_[pos_]))) {
        ++pos_;
    }
}

Token Lexer::readNumber() {
    bool seenDot = false;
    size_t start = pos_;

    while (pos_ < input_.size()) {
        char c = input_[pos_];

        if (std::isdigit(c)) {
            ++pos_;
        }
        else if (c == '.') {
            if (seenDot) {
                throw std::runtime_error("Error: bad format");
            }
            seenDot = true;
            ++pos_;
        }
        else {
            break;
        }
    }

    return {
        TokenType::Number,
        input_.substr(start, pos_ - start)
    };
}