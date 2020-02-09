//
// Created by quepas on 08/02/2020.
//

#ifndef ARRR_AY_LLVM_NODE_H
#define ARRR_AY_LLVM_NODE_H

#include <string>

namespace ast {

    class Node {
    public:
        Node() {}

        virtual std::string to_string() = 0;
    };

}

#endif //ARRR_AY_LLVM_NODE_H
