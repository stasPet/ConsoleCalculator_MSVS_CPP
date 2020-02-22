#include "AST.h"

using namespace clc::prs;

void AST::InsertToken(Token token)
{
    Node* temp = buffer.front();
    buffer.pop_front();

    temp->left = new Node{};
    temp->right = new Node{};

    buffer.push_back(temp->left);
    buffer.push_back(temp->right);

    buffer.front()->value = token;
}