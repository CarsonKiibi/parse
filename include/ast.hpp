#include <string>
#include <memory>

class Node {
    public:
        virtual double eval() const = 0; // every derived class must implement eval, and 
        virtual ~Node() = default;
};

// will always be leaf (no children)
class NumberNode : public Node {
    public:
        explicit NumberNode(double value);
        double eval() const override;

    private:
        double value_;
};

class UnaryOpNode : public Node {
    public:
        UnaryOpNode(char op,
                    std::unique_ptr<Node> child);

        double eval() const override;

    private:
            char op_;
            // Unary op will always have exactly one child
            // child_ could be another UnaryOp or a number
            std::unique_ptr<Node> child_;
};

class BinaryOpNode : public Node {
    public:
        BinaryOpNode(char op,
                    std::unique_ptr<Node> left,
                    std::unique_ptr<Node> right);

        double eval() const override;

    private: 
        char op_;
        // Binary op will always have exactly 2 children
        // left_ or right_ could be UnaryOp,BinaryOp, or number
        std::unique_ptr<Node> left_;
        std::unique_ptr<Node> right_;
};