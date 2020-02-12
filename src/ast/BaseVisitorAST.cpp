//
// Created by quepas on 10/02/2020.
//

#include "BaseVisitorAST.h"
#include "AST.h"

using std::any;

any BaseVisitorAST::visit(ast::Node *ast_tree) {
    return ast_tree->accept(this);
}

any BaseVisitorAST::visitChildren(ast::Node *ast_tree) {
    any result = defaultResult();
    for (auto &node : ast_tree->GetTraversalOrder()) {
        if (!shouldVisitNextChild(ast_tree, result)) {
            break;
        }
        any childResult = node->accept(this);
        result = aggregateResult(result, childResult);
    }
    return any();
}

any BaseVisitorAST::defaultResult() {
    return any();
}

any BaseVisitorAST::aggregateResult(any current_result, any next_result) {
    return next_result;
}

bool BaseVisitorAST::shouldVisitNextChild(ast::Node *ast_node, any current_result) {
    return true;
}

any BaseVisitorAST::visitNumber(ast::Number *number) {
    return visitChildren(number);
}

any BaseVisitorAST::visitBinaryOp(ast::BinaryOp *binary_op) {
    return visitChildren(binary_op);
}

any BaseVisitorAST::visitParentheses(ast::Parentheses *parentheses) {
    return visitChildren(parentheses);
}

any BaseVisitorAST::visitProgram(ast::Program *program) {
    return visitChildren(program);
}

any BaseVisitorAST::visitArray(ast::Array *array) {
    return visitChildren(array);
}
