//
// Created by quepas on 10/02/2020.
//

#ifndef ARRR_AY_LLVM_BASEVISITORAST_H
#define ARRR_AY_LLVM_BASEVISITORAST_H

#include "VisitorAST.h"

class BaseVisitorAST : public VisitorAST {
public:
    std::any visit(ast::Node *ast_tree) override;

    std::any visitChildren(ast::Node *ast_tree) override;

    std::any defaultResult() override;

    std::any aggregateResult(std::any current_result, std::any next_result) override;

    bool shouldVisitNextChild(ast::Node *ast_node, std::any current_result) override;

    std::any visitNumber(ast::Number *number) override;

    std::any visitBinaryOp(ast::BinaryOp *binary_op) override;

    std::any visitParentheses(ast::Parentheses *parentheses) override;

    std::any visitProgram(ast::Program *program) override;

};


#endif //ARRR_AY_LLVM_BASEVISITORAST_H
