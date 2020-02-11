#include "antlr4-runtime.h"
#include "parser/arrr_ayLexer.h"
#include "parser/arrr_ayParser.h"
#include "ast/PrintAST.h"
#include "ast/AST.h"
#include "ast/BuildAST.h"
#include "codegen/EasyCodegen.h"

#include <iostream>

int main() {
    antlr4::ANTLRInputStream input("1+2;");
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

    EasyCodegen easy_codegen;
    auto val = easy_codegen.visit(ast_root.get());
    llvm::Value* value = std::any_cast<llvm::Value*>(val);
    value->print(llvm::errs(), false);
    return 0;
}