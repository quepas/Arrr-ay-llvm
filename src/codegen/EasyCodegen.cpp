//
// Created by quepas on 11/02/2020.
//

#include "../ast/AST.h"
#include "EasyCodegen.h"

#include <llvm/IR/Constants.h>
#include <iostream>
#include <memory>

using std::any_cast;
using std::any;

any EasyCodegen::visitNumber(ast::Number *number) {
    return static_cast<llvm::Value *>(llvm::ConstantFP::get(context, llvm::APFloat(number->getValue())));
}

any EasyCodegen::visitBinaryOp(ast::BinaryOp *binary_op) {
    auto *left = any_cast<llvm::Value *>(visit(binary_op->getLeft().get()));
    auto *right = any_cast<llvm::Value *>(visit(binary_op->getRight().get()));

    switch (binary_op->getOp()) {
        case ast::BinaryOp::ADD:
            return builder->CreateFAdd(left, right, "addtmp");
        case ast::BinaryOp::SUB:
            return builder->CreateFSub(left, right, "subtmp");
        case ast::BinaryOp::MUL:
            return builder->CreateFMul(left, right, "multmp");
        case ast::BinaryOp::DIV:
            return builder->CreateFDiv(left, right, "divtmp");
        default:
            std::cout << "Error: unsupported binary operation" << std::endl;
    }
}

any EasyCodegen::visitParentheses(ast::Parentheses *parentheses) {
    return BaseVisitorAST::visitParentheses(parentheses);
}

any EasyCodegen::visitProgram(ast::Program *program) {
    // Create anonymous function
    std::vector<llvm::Type *> types;
    llvm::FunctionType *function_type = llvm::FunctionType::get(llvm::Type::getDoubleTy(context), types, false);
    llvm::Function *function = llvm::Function::Create(function_type, llvm::Function::InternalLinkage, "lambda_anon",
                                                      module.get());
    auto expr = program->getExpressions()[0];
    auto expr_val = visit(expr.get());
    // Create basic block
    llvm::BasicBlock *basic_block = llvm::BasicBlock::Create(context, "entry", function);
    builder->SetInsertPoint(basic_block);
    builder->CreateRet(std::any_cast<llvm::Value *>(expr_val));
    return static_cast<llvm::Value *>(function);
}

EasyCodegen::~EasyCodegen() {
    delete builder;
}

EasyCodegen::EasyCodegen(llvm::LLVMContext &context, std::unique_ptr<llvm::Module> &module) : context(context),
                                                                                              module(module) {
    builder = new llvm::IRBuilder(context);
}

