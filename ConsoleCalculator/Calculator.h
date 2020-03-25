#pragma once
#include "Parser/Parser.h"

namespace clc
{
    class Calculator
    {
    private:
        prs::Parser parser;
        prs::lxr::TableOfSymbols<> & tableOfSymbols;

    public:
        Calculator(std::wistream &);

        std::wstring_view GetResult();
        std::wstring_view Calculate(std::wstring_view);
    };

    inline Calculator::Calculator(std::wistream & s) :
        parser{s}, tableOfSymbols{parser.GetTableOfSymbol() } {}
}