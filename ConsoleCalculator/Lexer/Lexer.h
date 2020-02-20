#pragma once

#include <iosfwd>

#include "StateMachine/StateMachine.h"

#include "Token.h"
#include "TableOfSymbols.h"

namespace clc::lxr
{
    class Lexer
    {
    private:
        std::wistream & stream;
        TableOfSymbols & tableOfSymbols;

        CharType charBuffer;
        ExpressionStringType stringBuffer;

        Token currentToken;

        StateMachine stateMachine;

    public:
        explicit Lexer(std::wistream &, TableOfSymbols &);
        Lexer(const Lexer &) = delete;

        Token GetToken();
        void PutToken(Token);
    };

    inline Lexer::Lexer(std::wistream & s, TableOfSymbols & t) :
            stream{s}, tableOfSymbols{t}
    {
        // ...
    }
}