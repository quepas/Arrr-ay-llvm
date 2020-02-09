//
// Created by quepas on 09/02/2020.
//

#ifndef ARRR_AY_LLVM_PROGRAM_H
#define ARRR_AY_LLVM_PROGRAM_H

#include <utility>
#include <vector>
#include <memory>
#include "Node.h"
#include "Expression.h"

namespace ast {

    class Program : public Node {
    public:
        explicit Program(std::vector<std::shared_ptr<Expression>> expressions) : expressions(std::move(expressions)) {}

        std::string to_string() override {
            std::string str;
            for (auto& expr : expressions) {
                str += expr->to_string() + ";\n";
            }
            return str;
        }

    private:
        std::vector<std::shared_ptr<Expression>> expressions;
    };

}


#endif //ARRR_AY_LLVM_PROGRAM_H
