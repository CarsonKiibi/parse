#include <parse.hpp>
#include <stdexcept>

Parser::Parser(Lexer lexer) :
    lexer_(std::move(lexer))
    {
        advance();
    }

// parse is entry point to our parse helpers
// parse helpers return our subtrees
std::unique_ptr<Node> Parser::parse() {
    auto root = parseExpr();
    expect(TokenType::End, "Expected end of input");
    return root;
}

// parseExpr handles addition and subtraction (lowest precedence)
std::unique_ptr<Node> Parser::parseExpr() {
    auto left = parseTerm();

    while (true) {
        if (match(TokenType::Plus)) {
            auto right = parseTerm();
            left = std::make_unique<BinaryOpNode>('+', std::move(left), std::move(right));
        } else if (match(TokenType::Minus)) {
            auto right = parseTerm();
            left = std::make_unique<BinaryOpNode>('-', std::move(left), std::move(right));
        } else {
            break;
        }
    }

    return left;
}

// parseTerm handles multiplication and division (higher precedence)
std::unique_ptr<Node> Parser::parseTerm() {
    auto left = parseFactor();

    while (true) {
        if (match(TokenType::Multiply)) {
            auto right = parseFactor();
            left = std::make_unique<BinaryOpNode>('*', std::move(left), std::move(right));
        } else if (match(TokenType::Divide)) {
            auto right = parseFactor();
            left = std::make_unique<BinaryOpNode>('/', std::move(left), std::move(right));
        } else {
            break;
        }
    }

    return left;
}

// parseFactor handles unary operators, parentheses, and numbers (highest precedence)
std::unique_ptr<Node> Parser::parseFactor() {
    // unary minus
    if (match(TokenType::Minus)) {
        auto child = parseFactor();
        return std::make_unique<UnaryOpNode>('-', std::move(child));
    }

    // unary plus
    if (match(TokenType::Plus)) {
        auto child = parseFactor();
        return std::make_unique<UnaryOpNode>('+', std::move(child));
    }

    // parentheses
    if (match(TokenType::LParen)) {
        auto expr = parseExpr();
        expect(TokenType::RParen, "Expected closing parenthesis");
        advance();
        return expr;
    }

    // numbers
    if (check(TokenType::Number)) {
        double value = std::stod(current_.text);
        advance();
        return std::make_unique<NumberNode>(value);
    }

    throw std::runtime_error("Expected number, unary operator, or '('");
}

void Parser::advance() {
    current_ = lexer_.next();
}

bool Parser::check(TokenType type) const {
    return current_.type == type;
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

void Parser::expect(TokenType type, const std::string& message) {
    if (!check(type)) {
        throw std::runtime_error(message);
    }
}