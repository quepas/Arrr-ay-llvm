//
// Created by quepas on 08/02/2020.
//

#ifndef ARRR_AY_LLVM_PARENTHESES_H
#define ARRR_AY_LLVM_PARENTHESES_H

#include <utility>

#include "Expression.h"

namespace ast {

    class Parentheses : public Expression {
    private:
        std::shared_ptr<Expression> expr;
    public:
        explicit Parentheses(std::shared_ptr<Expression> expr) : expr(std::move(expr)) {}

        std::string to_string() override {
            return "(" + expr->to_string() + ")";
        }
    };

}

#endif //ARRR_AY_LLVM_PARENTHESES_H
