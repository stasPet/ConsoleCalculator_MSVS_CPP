#include "AST.h"

using namespace clc::prs;

AST::AST(AST && a)
{
    rootNode = a.rootNode;
    currentNode = a.currentNode;

    a.rootNode = nullptr;
    a.currentNode = nullptr;

    stackValue.swap(a.stackValue);
}

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
            rootNode = new Node{token};

            // If the operation is unary
            if (stackValue.empty() )
                stackValue.push(new Node{} );

            rootNode->right = stackValue.top();
            stackValue.pop();

            // If the operation is unary
            if (stackValue.empty() )
                stackValue.push(new Node{} );

            rootNode->left = stackValue.top();
            stackValue.pop();

            stackValue.push(rootNode);
        }
    }

    rootNode = stackValue.top();
    stackValue.pop();

    currentNode = rootNode;
}

Token AST::GetNextToken()
{
    Token returnValue;

    while (!stackValue.empty() || currentNode)
    {
        if (currentNode)
        {
            stackValue.push(currentNode);
            currentNode = currentNode->left;
        }
        else
        {
            currentNode = stackValue.top();
            stackValue.pop();

            returnValue = currentNode->value;
            currentNode = currentNode->right;

            break;
        }
    }

    return returnValue;
}

AST::Node::~Node()
{
    delete left;
    delete right;
}