#include "AST.h"

using namespace clc::prs;
using namespace clc;

void AST::InsertToken(lxr::Token token)
{
    Node* temp = buffer.front();
    buffer.pop_front();

    temp->left = new Node{};
    temp->right = new Node{};

    buffer.push_back(temp->left);
    buffer.push_back(temp->right);

    buffer.front()->value = token;
}