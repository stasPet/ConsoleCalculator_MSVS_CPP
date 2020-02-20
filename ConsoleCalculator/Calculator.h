#pragma once

#include "TableOfSymbols.h"
#include "Parser/Parser.h"

namespace clc
{
    class Calculator
    {
    private:
        TableOfSymbols tableOfSymbol;
        prs::Parser parser{std::wcin, tableOfSymbol};

    public:
        Calculator() = default;
        Calculator(std::wistream &);

    };

    inline Calculator::Calculator(std::wistream & s) : parser{s, tableOfSymbol}
    {
        parser.GetAST();
        // ...
    }
}