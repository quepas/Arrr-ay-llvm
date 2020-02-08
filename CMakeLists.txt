cmake_minimum_required(VERSION 3.0)

project(Arrr-ay-llvm VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)

# Add and build ANTLR parser generator
set(ANTLR_CPP_DIR third-party/antlr4/runtime/Cpp/)
add_subdirectory(${ANTLR_CPP_DIR})
# Generate grammar
execute_process (
        COMMAND bash -c "${PROJECT_SOURCE_DIR}/grammar/generate.sh"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/grammar
        COMMAND_ECHO STDOUT
)

# Add pre-installed LLVM
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS} ${ANTLR_CPP_DIR}/runtime/src)
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(LLVM_LIBS Core ExecutionEngine Interpreter MC MCJIT Support nativecodegen)

add_executable(arrr-ay-repl src/main.cpp)
target_link_libraries(arrr-ay-repl ${LLVM_LIBS} antlr4_static)
