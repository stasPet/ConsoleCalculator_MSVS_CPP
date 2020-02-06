#pragma once

#include "../Lexer/Lexeme.h"

namespace clc::psr
{
    class TokenTree
    {
    private:
        lxr::Lexeme value;

        TokenTree * left;
        TokenTree * right;

    public:

    };
}