//
// Created by quepas on 10/02/2020.
//

#ifndef ARRR_AY_LLVM_VISITORAST_H
#define ARRR_AY_LLVM_VISITORAST_H

namespace ast {
    class Node;
    class Number;
    class BinaryOp;
    class Parentheses;
    class Program;
}

#include <any>

class VisitorAST {

public:
    // Visitor methods
    virtual std::any visit(ast::Node* ast_tree) = 0;

    virtual std::any visitChildren(ast::Node* ast_tree) = 0;

    virtual std::any defaultResult() = 0;

    virtual std::any aggregateResult(std::any current_result, std::any next_result) = 0;

    virtual bool shouldVisitNextChild(ast::Node* ast_node, std::any current_result) = 0;

    // AST nodes
    virtual std::any visitNumber(ast::Number *number) = 0;

    virtual std::any visitBinaryOp(ast::BinaryOp *binary_op) = 0;

    virtual std::any visitParentheses(ast::Parentheses *parentheses) = 0;

    virtual std::any visitProgram(ast::Program *program) = 0;

};


#endif //ARRR_AY_LLVM_VISITORAST_H
