#pragma once

#include <memory>
#include "Lexer/Lexeme.h"

namespace clc::lxr
{
    struct IState
    {
        virtual ~IState() {}

        virtual LexemeType Set(WChar) = 0;
        virtual void Reset() = 0;

        virtual LexemeType GetLexemeType() = 0;

        static std::unique_ptr<IState> Factory(LexemeType);
    };
}