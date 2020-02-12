//
// Created by quepas on 11/02/2020.
//

#include "EasyJIT.h"
#include "../codegen/EasyCodegen.h"

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/TargetSelect.h>
#include <iostream>

EasyJIT::EasyJIT() {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
}

void EasyJIT::Execute(ast::Node *ast_tree) {
    llvm::LLVMContext context;
    auto module = std::make_unique<llvm::Module>("arrr-ay-jit", context);

    EasyCodegen easy_codegen(context, module);
    auto val = easy_codegen.visit(ast_tree);
    llvm::Value *value = std::any_cast<llvm::Value *>(val);
    value->print(llvm::errs(), false);

    std::vector<llvm::GenericValue> Args(0);
    std::string error_str;
    llvm::ExecutionEngine *execution_engine = llvm::EngineBuilder(std::move(module))
            .setErrorStr(&error_str)
            .create();
    std::cout << "Errors=" << error_str << std::endl;
    llvm::GenericValue result = execution_engine->runFunction(static_cast<llvm::Function *>(value), Args);
    std::cout << "Result=" << result.DoubleVal << std::endl;
}
