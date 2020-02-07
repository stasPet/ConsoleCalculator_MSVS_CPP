#pragma once

#include <iosfwd>

#include "Token.h"
#include "StateMachine/StateMachine.h"
#include "../TableOfSymbols.h"

namespace clc::lxr
{
    class Lexer
    {
    private:
        std::wistream & stream;
        TableOfSymbols & tableOfSymbols;

        CharType charBuffer;
        ExpressionStringType stringBuffer;
        Token token;

        StateMachine stateMachine;

    public:
        explicit Lexer(std::wistream &, TableOfSymbols &);
        Lexer(const Lexer &) = delete;

        Token GetToken();
        void PutToken(Token);

        void Reset(std::wistream &, TableOfSymbols &);
    };

    inline Lexer::Lexer(std::wistream & s, TableOfSymbols & t) :
            stream{s}, tableOfSymbols{t}
    {
        // ...
    }

    inline void Lexer::Reset(std::wistream &, TableOfSymbols &)
    {
        // TODO
    }
}