#include "AST.h"

using namespace clc::prs;

void AST::SetTokenBuffer(std::queue<Token> tokenBuffer)
{
    Token token;
    while (!tokenBuffer.empty() )
    {
        token = tokenBuffer.front();
        tokenBuffer.pop();

        if (token.tokenType != TokenType::Operation)
        {
            stackValue.push(new Node{token} );
        }
        else
        {
            root = new Node{token};

            if (stackValue.empty() )
                stackValue.push(new Node{} );

            right = stackValue.top();
            stackValue.pop();

            if (stackValue.empty() )
                stackValue.push(new Node{} );

            left = stackValue.top();
            stackValue.pop();

            root->right = right;
            root->left = left;

            stackValue.push(root);
        }
    }

    root = stackValue.top();
    stackValue.pop();

    left = nullptr;
    right = nullptr;
}

Token AST::GetNextToken()
{
    return Token{};
}