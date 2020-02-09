//
// Created by quepas on 08/02/2020.
//

#ifndef ARRR_AY_LLVM_BINARYOP_H
#define ARRR_AY_LLVM_BINARYOP_H

#include <utility>

#include "Expression.h"

namespace ast {

    class BinaryOp : public Expression {
    public:
        enum Op {
            ADD,
            SUB,
            MUL,
            DIV
        };

        std::string to_string() override {
            std::string op_str;
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

    private:
        std::shared_ptr<ast::Expression> left, right;
        Op op;
    public:
        BinaryOp(Op op, std::shared_ptr<ast::Expression> left, std::shared_ptr<ast::Expression> right)
                : op(op), left(std::move(left)), right(std::move(right)) {}
    };

}

#endif //ARRR_AY_LLVM_BINARYOP_H
