#pragma once

#include "AliasType.h"
#include "Lexer/Token.h"

#include <list>

namespace clc::prs
{
    class AST
    {
    private:
        struct Node
        {
            lxr::Token value;

            Node * left = nullptr;
            Node * right = nullptr;
        };

        std::list<Node*> buffer;

    public:
        AST(lxr::Token);

        void InsertToken(lxr::Token);
        lxr::Token GetToken();
    };

    inline AST::AST(lxr::Token token) : buffer{new Node{token} } {}
}