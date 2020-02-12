//
// Created by quepas on 10/02/2020.
//

#ifndef ARRR_AY_LLVM_AST_H
#define ARRR_AY_LLVM_AST_H

#include <any>
#include <memory>
#include <string>
#include <vector>

class VisitorAST;

namespace ast {

    class Node {
    public:
        Node() {}

        virtual std::string to_string() = 0;

        virtual std::any accept(VisitorAST *visitor) = 0;

        virtual std::vector<Node *> GetTraversalOrder() = 0;
    };

    class Expression : public Node {
    public:
        Expression() {}
    };

    class Number : public Expression {
    private:
        double value;
    public:
        explicit Number(double value) : value(value) {}

        std::string to_string() override;

        std::vector<Node *> GetTraversalOrder() override;

        std::any accept(VisitorAST *visitor) override;

        double getValue() const;

    };

    class Array : public Expression {
    private:
        std::vector<std::shared_ptr<Expression>> elements;
    public:
        Array(std::vector<std::shared_ptr<Expression>> elements);

        std::string to_string() override;

        std::any accept(VisitorAST *visitor) override;

        std::vector<Node *> GetTraversalOrder() override;

        const std::vector<std::shared_ptr<Expression>> &getElements() const;
    };

    class Parentheses : public Expression {
    private:
        std::shared_ptr<Expression> expr;
    public:
        explicit Parentheses(std::shared_ptr<Expression> expr) : expr(std::move(expr)) {}

        std::string to_string() override;

        std::vector<Node *> GetTraversalOrder() override;

        std::any accept(VisitorAST *visitor) override;
    };

    class BinaryOp : public Expression {
    public:
        enum Op {
            ADD,
            SUB,
            MUL,
            DIV
        };

        BinaryOp(Op op, std::shared_ptr<ast::Expression> left, std::shared_ptr<ast::Expression> right)
                : op(op), left(std::move(left)), right(std::move(right)) {}

        std::string to_string() override;

        std::vector<Node *> GetTraversalOrder() override;

        std::any accept(VisitorAST *visitor) override;

        const std::shared_ptr<ast::Expression> &getLeft() const;

        const std::shared_ptr<ast::Expression> &getRight() const;

        Op getOp() const;

    private:
        std::shared_ptr<ast::Expression> left, right;
        Op op;
    };

    class Program : public Node {
    public:
        explicit Program(std::vector<std::shared_ptr<Expression>> expressions) : expressions(std::move(expressions)) {}

        std::string to_string() override;

        std::vector<Node *> GetTraversalOrder() override;

        std::any accept(VisitorAST *visitor) override;

        const std::vector<std::shared_ptr<Expression>> &getExpressions() const;

    private:
        std::vector<std::shared_ptr<Expression>> expressions;
    };

}

#endif //ARRR_AY_LLVM_AST_H
