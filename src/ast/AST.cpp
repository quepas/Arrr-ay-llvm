//
// Created by quepas on 10/02/2020.
//

#include "AST.h"

#include <utility>
#include "VisitorAST.h"

using std::any;
using std::string;
using std::vector;

namespace ast {

    string Number::to_string() {
        return std::to_string(value);
    }

    vector<Node *> Number::GetTraversalOrder() {
        return vector<Node *>();
    }

    any Number::accept(VisitorAST *visitor) {
        return visitor->visitNumber(this);
    }

    double Number::getValue() const {
        return value;
    }

    string Parentheses::to_string() {
        return "(" + expr->to_string() + ")";
    }

    vector<Node *> Parentheses::GetTraversalOrder() {
        return vector<Node *>{expr.get()};
    }

    any Parentheses::accept(VisitorAST *visitor) {
        return visitor->visitParentheses(this);
    };

    string BinaryOp::to_string() {
        string op_str;
        switch (op) {
            case ADD:
                op_str = "+";
                break;
            case SUB:
                op_str = "-";
                break;
            case MUL:
                op_str = "*";
                break;
            case DIV:
                op_str = "/";
                break;
        }
        return left->to_string() + op_str + right->to_string();
    }

    vector<Node *> BinaryOp::GetTraversalOrder() {
        vector<Node *> result = {left.get(), right.get()};
        return result;
    }

    any BinaryOp::accept(VisitorAST *visitor) {
        return visitor->visitBinaryOp(this);
    }

    const std::shared_ptr<ast::Expression> &BinaryOp::getLeft() const {
        return left;
    }

    const std::shared_ptr<ast::Expression> &BinaryOp::getRight() const {
        return right;
    }

    BinaryOp::Op BinaryOp::getOp() const {
        return op;
    }

    string Program::to_string() {
        string str;
        for (auto &expr : expressions) {
            str += expr->to_string() + ";\n";
        }
        return str;
    }

    vector<Node *> Program::GetTraversalOrder() {
        vector<Node *> result;
        result.reserve(expressions.size());
        for (int idx = 0; idx < expressions.size(); ++idx) {
            result.push_back(expressions[idx].get());
        }
        return result;
    }

    any Program::accept(VisitorAST *visitor) {
        return visitor->visitProgram(this);
    }

    const vector<std::shared_ptr<Expression>> &Program::getExpressions() const {
        return expressions;
    }

    string Array::to_string() {
        string str = "[";
        for (int idx = 0; idx < elements.size(); ++idx) {
            str += elements[idx]->to_string();
            if (idx + 1 != elements.size()) {
                str += ", ";
            }
        }
        str += "]";
        return str;
    }

    any Array::accept(VisitorAST *visitor) {
        return visitor->visitArray(this);
    }

    vector<Node *> Array::GetTraversalOrder() {
        vector<Node *> result;
        result.reserve(elements.size());
        for (int idx = 0; idx < elements.size(); ++idx) {
            result.push_back(elements[idx].get());
        }
        return result;
    }

    Array::Array(vector<std::shared_ptr<Expression>> elements) : elements(std::move(elements)) {}

    const vector<std::shared_ptr<Expression>> &Array::getElements() const {
        return elements;
    }
}