#pragma once

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

namespace clc
{
    class Calculator
    {
    private:
        lxr::Lexer lexer;
        prs::Parser parser;

        std::wstring result;

        static prs::TokenType GetTokenType(lxr::LexemeType);

    public:
        std::wstring Calculate(std::wistream &);
    };
}