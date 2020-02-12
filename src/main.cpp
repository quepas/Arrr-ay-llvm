#include "antlr4-runtime.h"
#include "parser/arrr_ayLexer.h"
#include "parser/arrr_ayParser.h"
#include "ast/PrintAST.h"
#include "ast/AST.h"
#include "ast/BuildAST.h"

#include <iostream>
#include "jit/EasyJIT.h"

int main() {
    EasyJIT easy_jit;

    while (true) {
        std::cout << "> ";
        std::string command;
        std::cin >> command;
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

    return 0;
}