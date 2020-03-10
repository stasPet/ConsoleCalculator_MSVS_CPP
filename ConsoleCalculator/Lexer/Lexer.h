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
        Lexer();
        Lexer(std::initializer_list<LexemeType> );
        Lexeme GetLexeme(std::wistream &);
    };

    inline Lexer::Lexer() :
        stateMachine
        {
            LexemeType::Number,
            LexemeType::Name,
            LexemeType::Operation,
            LexemeType::Function,
            LexemeType::LeftParenthesis,
            LexemeType::RightParenthesis
        }
    {
    
    }
    inline Lexer::Lexer(std::initializer_list<LexemeType> l) :
        stateMachine{l}
    {
    
    }
}