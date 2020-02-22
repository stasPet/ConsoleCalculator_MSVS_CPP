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

        TableOfSymbols<lxr::String, std::size_t> tableOfSymbol;

        lxr::String result;

    public:
        Calculator() {};

        lxr::String const & GetResult();
        lxr::String const & Calculate(std::wistream&);
    };

    inline lxr::String const & Calculator::GetResult()
    {
        return result;
    }
}