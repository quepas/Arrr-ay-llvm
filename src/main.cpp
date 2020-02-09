#include "antlr4-runtime.h"
#include "parser/arrr_ayLexer.h"
#include "parser/arrr_ayParser.h"
#include "ast/BuildAST.h"
#include "ast/Node.h"
#include "ast/Program.h"

#include <iostream>

int main() {
    antlr4::ANTLRInputStream input("1+2-(3/4);2+3;");
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

    return 0;
}