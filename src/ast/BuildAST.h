//
// Created by quepas on 08/02/2020.
//

#ifndef ARRR_AY_LLVM_BUILDAST_H
#define ARRR_AY_LLVM_BUILDAST_H

#include "../parser/arrr_ayBaseVisitor.h"

class BuildAST : public arrr_ayBaseVisitor {

public:

    antlrcpp::Any visitNumber(arrr_ayParser::NumberContext *context) override;

    antlrcpp::Any visitExprAddSub(arrr_ayParser::ExprAddSubContext *context) override;

    antlrcpp::Any visitExprNumber(arrr_ayParser::ExprNumberContext *context) override;

    antlrcpp::Any visitExprMulDiv(arrr_ayParser::ExprMulDivContext *context) override;

    antlrcpp::Any visitExprParentheses(arrr_ayParser::ExprParenthesesContext *context) override;

    antlrcpp::Any visitProgram(arrr_ayParser::ProgramContext *context) override;

};


#endif //ARRR_AY_LLVM_BUILDAST_H
