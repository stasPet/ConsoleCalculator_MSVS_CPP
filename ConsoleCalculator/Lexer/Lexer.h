#pragma once

#include <iosfwd>
#include "StateMachine/StateMachine.h"

namespace clc::lxr
{
    class Lexer
    {
    private:
        Char charBuffer;
        String stringBuffer;

        Lexeme currentLexeme;
        StateMachine stateMachine;

    public:
        Lexeme GetLexeme(std::wistream &);
    };
}