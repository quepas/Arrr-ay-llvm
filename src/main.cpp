#include "antlr4-runtime.h"
#include "parser/arrr_ayLexer.h"
#include "parser/arrr_ayParser.h"
#include "ast/PrintAST.h"
#include "ast/AST.h"
#include "ast/BuildAST.h"
#include "codegen/EasyCodegen.h"

#include <iostream>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"

int main() {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();

    antlr4::ANTLRInputStream input("1+2-5+134;");
    arrr_ayLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    tokens.fill();

    arrr_ayParser parser(&tokens);
    antlr4::tree::ParseTree* tree = parser.program();

    std::cout << "Concrete tree: " << tree->toStringTree(&parser) << std::endl;

    std::shared_ptr<ast::Program> ast_root;
    BuildAST build_ast;
    ast_root = build_ast.visit(tree);

    std::cout << "Abstract tree: \n" << ast_root->to_string() << std::endl;

    PrintAST printAst;
    printAst.visit(ast_root.get());

    llvm::LLVMContext context;
    auto module = std::make_unique<llvm::Module>("arrr-ay-jit", context);

    EasyCodegen easy_codegen(context, module);
    auto val = easy_codegen.visit(ast_root.get());
    llvm::Value* value = std::any_cast<llvm::Value*>(val);
    value->print(llvm::errs(), false);

    std::vector<llvm::GenericValue> Args(0);
    std::string error_str;
    llvm::ExecutionEngine* execution_engine = llvm::EngineBuilder(std::move(module))
            .setErrorStr(&error_str)
            .create();
    std::cout << "Errors=" << error_str << std::endl;
    llvm::GenericValue result = execution_engine->runFunction(static_cast<llvm::Function *>(value), Args);
    std::cout << "Result=" << result.DoubleVal << std::endl;
    return 0;
}