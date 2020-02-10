//
// Created by quepas on 10/02/2020.
//

#include "AST.h"
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
        for (int i = 0; i < expressions.size(); ++i) {
            result.push_back(expressions[i].get());
        }
        return result;
    }

    any Program::accept(VisitorAST *visitor) {
        return visitor->visitProgram(this);
    }

}