//
// Created by quepas on 11/02/2020.
//

#ifndef ARRR_AY_LLVM_EASYJIT_H
#define ARRR_AY_LLVM_EASYJIT_H


#include "../ast/AST.h"

class EasyJIT {

public:
    EasyJIT();

    void Execute(ast::Node *ast_tree);


};


#endif //ARRR_AY_LLVM_EASYJIT_H
