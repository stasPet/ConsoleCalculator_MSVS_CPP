#pragma once

#include "../Lexer/Token.h"

namespace clc::psr
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

    public:

    };
}