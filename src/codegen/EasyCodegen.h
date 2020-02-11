//
// Created by quepas on 11/02/2020.
//

#ifndef ARRR_AY_LLVM_EASYCODEGEN_H
#define ARRR_AY_LLVM_EASYCODEGEN_H

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include "../ast/BaseVisitorAST.h"

class EasyCodegen : public BaseVisitorAST {

public:
    EasyCodegen(llvm::LLVMContext &context, std::unique_ptr<llvm::Module> &module);

    virtual ~EasyCodegen();

    std::any visitBinaryOp(ast::BinaryOp *binary_op) override;

    std::any visitParentheses(ast::Parentheses *parentheses) override;

    std::any visitProgram(ast::Program *program) override;

    std::any visitNumber(ast::Number *number) override;

private:
    llvm::LLVMContext& context;
    llvm::IRBuilder<> *builder;
    std::unique_ptr<llvm::Module>& module;

};


#endif //ARRR_AY_LLVM_EASYCODEGEN_H
