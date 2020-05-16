#pragma once
#include "Parser/Parser.h"

namespace clc
{
    class Calculator
    {
    private:
        prs::Parser parser;
        prs::lxr::TableOfSymbols<> & tableOfSymbols;

        std::wistream & inputStream;

        double GetNumber(prs::lxr::Token);

    public:
        Calculator(std::wistream &);

        Calculator(Calculator const &) = delete;
        Calculator(Calculator &&) = default;

        ~Calculator() = default;

        Calculator & operator=(Calculator const &) = delete;
        Calculator & operator=(Calculator &&) = default;
        
        operator bool();

        double GetResult();
    };

    inline Calculator::Calculator(std::wistream & s) :
        parser{s}, inputStream{s}, tableOfSymbols{parser.GetTableOfSymbol() }
    {}

    inline Calculator::operator bool()
    {
        return parser;
    }
}