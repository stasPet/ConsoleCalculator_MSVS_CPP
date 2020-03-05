#pragma once

#include "TableOfSymbols.h"
#include "AST.h"

namespace clc::prs
{
    using TableOfSymbolsT = 
        TableOfSymbols<std::wstring, std::size_t>;

    using Priority = char;

    class Parser
    {
    private:
        TableOfSymbolsT tableOfSymbol;

        std::stack<Token> stackValue;

        std::queue<Token> ShuntingYard(std::queue<Token> );
        Priority GetPriority(Token);

    public:
        AST GetAST(std::queue<Token> );
        TableOfSymbolsT & GetTableOfSymbols();
    };

    inline TableOfSymbolsT & Parser::GetTableOfSymbols()
    {
        return tableOfSymbol;
    }
}