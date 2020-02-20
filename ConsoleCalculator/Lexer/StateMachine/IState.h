#pragma once
#include "Lexer/Token.h"

namespace clc::lxr
{
    struct IState
    {
        virtual ~IState() {}

        virtual TokenType Set(CharType) = 0;
        virtual void Reset() = 0;

        virtual TokenType GetTokenType() = 0;
    };
}