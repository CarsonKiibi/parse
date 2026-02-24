#include <ast.hpp>
#include <stdexcept>

NumberNode::NumberNode(double value)
    : value_(value) {}

double NumberNode::eval() const {
    return value_;
}

UnaryOpNode::UnaryOpNode(char op, std::unique_ptr<Node> child)
    : op_(op), child_(std::move(child)) {}

double UnaryOpNode::eval() const {
    double childVal = child_->eval();

    switch (op_) {
        case '-':
            return -childVal;
        case '+':
            return childVal;
        default:
            throw std::runtime_error("Unknown unary operator");
    }
}

BinaryOpNode::BinaryOpNode(char op, std::unique_ptr<Node> left, std::unique_ptr<Node> right)
    : op_(op), left_(std::move(left)), right_(std::move(right)) {}

double BinaryOpNode::eval() const {
    double leftVal = left_->eval();
    double rightVal = right_->eval();

    switch (op_) {
        case '+':
            return leftVal + rightVal;
        case '-':
            return leftVal - rightVal;
        case '*':
            return leftVal * rightVal;
        case '/':
            if (rightVal == 0.0) {
                throw std::runtime_error("Division by zero");
            }
            return leftVal / rightVal;
        default:
            throw std::runtime_error("Unknown binary operator");
    }
}