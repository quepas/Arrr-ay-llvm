//
// Created by quepas on 08/02/2020.
//

#ifndef ARRR_AY_LLVM_NUMBER_H
#define ARRR_AY_LLVM_NUMBER_H

#include "Expression.h"

namespace ast {

    class Number : public Expression {
    private:
        double value;
    public:
        explicit Number(double value) : value(value) {}

        std::string to_string() override {
            return std::to_string(value);
        }
    };

}

#endif //ARRR_AY_LLVM_NUMBER_H
