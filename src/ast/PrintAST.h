//
// Created by quepas on 10/02/2020.
//

#ifndef ARRR_AY_LLVM_PRINTAST_H
#define ARRR_AY_LLVM_PRINTAST_H


#include <iostream>
#include "BaseVisitorAST.h"
#include "AST.h"

class PrintAST : public BaseVisitorAST {

public:
    std::any visitNumber(ast::Number *number) {
        std::cout << "Visit number=" << number->to_string() << std::endl;
        return 1;
    }

    std::any visitBinaryOp(ast::BinaryOp *binary_op) {
        std::cout << "Visit binary_op=" << binary_op->to_string() << std::endl;
        return 2;
    }

    std::any visitParentheses(ast::Parentheses *parentheses) {
        std::cout << "Visit parentheses=" << parentheses->to_string() << std::endl;
        return 3;
    }

    std::any visitProgram(ast::Program *program) {
        std::cout << "Visit program=" << program->to_string() << std::endl;
        return 4;
    }

};


#endif //ARRR_AY_LLVM_PRINTAST_H
