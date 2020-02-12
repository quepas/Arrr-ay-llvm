#include "antlr4-runtime.h"
#include "parser/arrr_ayLexer.h"
#include "parser/arrr_ayParser.h"
#include "ast/PrintAST.h"
#include "ast/AST.h"
#include "ast/BuildAST.h"

#include <iostream>
#include "jit/EasyJIT.h"

void execute(EasyJIT &easy_jit, const std::string &command) {
    antlr4::ANTLRInputStream input(command);
    arrr_ayLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    tokens.fill();

    arrr_ayParser parser(&tokens);
    antlr4::tree::ParseTree *tree = parser.program();

    std::cout << "Concrete tree: " << tree->toStringTree(&parser) << std::endl;

    std::shared_ptr<ast::Program> ast_root;
    BuildAST build_ast;
    ast_root = build_ast.visit(tree);

    std::cout << "Abstract tree: \n" << ast_root->to_string() << std::endl;

    PrintAST printAst;
    printAst.visit(ast_root.get());

    easy_jit.Execute(ast_root.get());
}

int main(int argc, char **argv) {
    EasyJIT easy_jit;

    if (argc > 1) {
        std::cout << "args=" << argv[1] << std::endl;
        execute(easy_jit, argv[1]);
    } else {
        while (true) {
            std::cout << "> ";
            std::string command;
            std::cin >> command;
            execute(easy_jit, command);
        }
    }
}