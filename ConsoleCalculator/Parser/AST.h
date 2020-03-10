#pragma once

#include "Parser/Token.h"

#include <queue>
#include <stack>

#include <iostream>

#include "TableOfSymbols.h"

namespace clc::prs
{
    class AST
    {
    private:
        using TableOfSymbolsT = 
            TableOfSymbols<std::wstring, std::size_t>;

        struct Node
        {
            Token value;

            Node * left;
            Node * right;

            ~Node();
        };

        Node * rootNode{};
        Node * currentNode{};

        std::stack<Node *> stackValue;

    public:
        AST() = default;
        AST(AST const &) = delete;

        AST(std::queue<Token> );
        AST(AST &&);

        ~AST();

        void SetTokenBuffer(std::queue<Token> );
        Token GetNextToken();
    };

    inline AST::AST(std::queue<Token> q)
    {
        SetTokenBuffer(std::move(q) );
    }
    
    inline AST::~AST()
    {
        delete rootNode;
    }
}