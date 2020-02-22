#pragma once

#include "Parser/Token.h"

#include <list>

namespace clc::prs
{
    class AST
    {
    private:
        struct Node
        {
            Token value;

            Node * left = nullptr;
            Node * right = nullptr;
        };

        std::list<Node*> buffer;

    public:
        AST() = default;
        AST(Token);

        void InsertToken(Token);
        Token GetToken();
    };

    inline AST::AST(Token token) : buffer{new Node{token} } {}
}