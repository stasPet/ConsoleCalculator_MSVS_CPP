#pragma once
#include "Lexer/Token.h"

namespace clc::prs
{
    struct Node
    {
        Node * ln;
        Node * rn;

        lxr::Token tv;

        Node(lxr::Token t, Node * l = nullptr, Node * r = nullptr) :
            tv{t}, ln{l}, rn{r} {}
    };

    class ParseTree
    {
    private:
        Node * root;

    public:
        ParseTree(Node * p) : root{p} {}
    };
}