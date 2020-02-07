#pragma once

#include "../Lexer/Token.h"

namespace clc::psr
{
    class AST
    {
    private:
        lxr::Token value;

        AST * left;
        AST * right;

    public:

    };
}