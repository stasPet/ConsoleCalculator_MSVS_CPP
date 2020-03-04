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
        };

        Node * root{};
        Node * left{};
        Node * right{};

        std::stack<Node *> stackValue;

    public:
        AST() = default;
        AST(std::queue<Token> );

        void SetTokenBuffer(std::queue<Token> );
        Token GetNextToken();

        Node * GetRoot();

        void Show(Node * node, TableOfSymbolsT & t)
        {
            while (!stackValue.empty() || node)
            {
                if (node)
                {
                    stackValue.push(node);
                    node = node->left;
                }
                else
                {
                    node = stackValue.top();
                    stackValue.pop();

                    std::wcout << t.GetSymbol(node->value.attribue) << ' ';

                    node = node->right;
                }
            }
        }
    };

    inline AST::AST(std::queue<Token> q)
    {
        SetTokenBuffer(std::move(q) );
    }

    inline AST::Node * AST::GetRoot()
    {
        return root;
    }
}