#pragma once

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

#include "TableOfSymbols.h"

namespace clc
{
    class Calculator
    {
    private:
        lxr::Lexer lexer;
        prs::Parser parser;

        TableOfSymbols<lxr::WString, std::size_t> tableOfSymbol;

        prs::AST ast;
        lxr::WString result;

        static prs::TokenType GetTokenType(lxr::Lexeme const &);

    public:
        //Calculator() = default;

        lxr::WString GetResult();
        lxr::WString Calculate(std::wistream &);
    };

    inline lxr::WString Calculator::GetResult()
    {
        return result;
    }
}