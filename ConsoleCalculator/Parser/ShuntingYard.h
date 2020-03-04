#pragma once

#include <queue>
#include <stack>

#include "Parser/Token.h"
#include "Parser/TableOfSymbols.h"

namespace clc::prs
{
    class ShuntingYard
    {
    private:
        using TableOfSymbolsT = 
            TableOfSymbols<std::wstring, std::size_t>;

        using Priority = char;

        std::stack<Token> stackValue;

        Priority currentPriority = 0;
        Priority GetPriority(Token, TableOfSymbolsT &);

    public:
        std::queue<Token> Transform(std::queue<Token>,
            TableOfSymbolsT &);
    };
}