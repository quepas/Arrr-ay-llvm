cmake_minimum_required(VERSION 3.0)

project(Arrr-ay-llvm VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)

# Add and build ANTLR parser generator
set(ANTLR_CPP_DIR third-party/antlr4/runtime/Cpp/)
add_subdirectory(${ANTLR_CPP_DIR})
# Generate grammar
execute_process(
        COMMAND bash -c "${PROJECT_SOURCE_DIR}/grammar/generate.sh"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/grammar
        COMMAND_ECHO STDOUT
)
# Group generated sources
set(ARRR_AY_PARSER_DIR ${PROJECT_SOURCE_DIR}/src/parser)
set(ARRR_AY_SOURCES
        ${ARRR_AY_PARSER_DIR}/arrr_ayBaseListener.cpp
        ${ARRR_AY_PARSER_DIR}/arrr_ayBaseVisitor.cpp
        ${ARRR_AY_PARSER_DIR}/arrr_ayLexer.cpp
        ${ARRR_AY_PARSER_DIR}/arrr_ayListener.cpp
        ${ARRR_AY_PARSER_DIR}/arrr_ayParser.cpp
        ${ARRR_AY_PARSER_DIR}/arrr_ayVisitor.cpp)

# Add pre-installed LLVM
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS} ${ANTLR_CPP_DIR}/runtime/src)
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(LLVM_LIBS Core ExecutionEngine Interpreter MC MCJIT Support nativecodegen)

add_executable(arrr-ay-repl
        ${ARRR_AY_SOURCES}
        src/main.cpp
        src/ast/BuildAST.cpp
        src/ast/BuildAST.h
        src/ast/VisitorAST.h
        src/ast/BaseVisitorAST.h
        src/ast/BaseVisitorAST.cpp
        src/ast/PrintAST.h
        src/ast/AST.cpp
        src/ast/AST.h
        src/codegen/EasyCodegen.cpp
        src/codegen/EasyCodegen.h)
target_link_libraries(arrr-ay-repl ${LLVM_LIBS} antlr4_static)
