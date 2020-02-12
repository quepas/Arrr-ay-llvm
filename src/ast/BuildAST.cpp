//
// Created by quepas on 08/02/2020.
//

#include "../parser/arrr_ayLexer.h"
#include "BuildAST.h"
#include "AST.h"

using antlrcpp::Any;
using std::make_shared;
using std::shared_ptr;
using std::stod;
using std::vector;

antlrcpp::Any BuildAST::visitNumber(arrr_ayParser::NumberContext *context) {
    shared_ptr<ast::Expression> result = make_shared<ast::Number>(stod(context->INT()->getText()));
    return result;
}

antlrcpp::Any BuildAST::visitExprAddSub(arrr_ayParser::ExprAddSubContext *context) {
    shared_ptr<ast::Expression> left = visit(context->left);
    shared_ptr<ast::Expression> right = visit(context->right);
    shared_ptr<ast::Expression> result;
    switch(context->op->getType()) {
        case arrr_ayLexer::ADD:
            result = make_shared<ast::BinaryOp>(ast::BinaryOp::ADD, left, right);
            break;
        case arrr_ayLexer::SUB:
            result = make_shared<ast::BinaryOp>(ast::BinaryOp::SUB, left, right);
            break;
    }
    return result;
}

antlrcpp::Any BuildAST::visitExprNumber(arrr_ayParser::ExprNumberContext *context) {
    return visitNumber(context->number());
}

antlrcpp::Any BuildAST::visitExprMulDiv(arrr_ayParser::ExprMulDivContext *context) {
    shared_ptr<ast::Expression> left = visit(context->left);
    shared_ptr<ast::Expression> right = visit(context->right);
    shared_ptr<ast::Expression> result;
    switch(context->op->getType()) {
        case arrr_ayLexer::MUL:
            result = make_shared<ast::BinaryOp>(ast::BinaryOp::MUL, left, right);
            break;
        case arrr_ayLexer::DIV:
            result = make_shared<ast::BinaryOp>(ast::BinaryOp::DIV, left, right);
            break;
    }
    return result;
}

antlrcpp::Any BuildAST::visitExprParentheses(arrr_ayParser::ExprParenthesesContext *context) {
    shared_ptr<ast::Expression> expr = visit(context->expr());
    shared_ptr<ast::Expression> parentheses = make_shared<ast::Parentheses>(expr);
    return parentheses;
}

antlrcpp::Any BuildAST::visitProgram(arrr_ayParser::ProgramContext *context) {
    vector<shared_ptr<ast::Expression>> program;
    program.reserve(context->expr().size());
    for (auto& expr : context->expr()) {
        program.push_back(visit(expr));
    }
    return make_shared<ast::Program>(program);
}

Any BuildAST::visitExprArray(arrr_ayParser::ExprArrayContext *ctx) {
    shared_ptr<ast::Expression> array;
    vector<shared_ptr<ast::Expression>> elements;
    elements.reserve(ctx->number().size());
    for (auto& expr : ctx->number()) {
        elements.push_back(visit(expr));
    }
    array = make_shared<ast::Array>(elements);
    return array;
}

