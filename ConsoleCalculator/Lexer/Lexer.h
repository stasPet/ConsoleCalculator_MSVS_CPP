#pragma once

#include <iosfwd>
#include "StateMachine/StateMachine.h"

namespace clc::lxr
{
    class Lexer
    {
    private:
        WChar charBuffer;
        WString stringBuffer;

        Lexeme currentLexeme;
        StateMachine stateMachine;

    public:
        Lexeme GetLexeme(std::wistream &);
    };
}