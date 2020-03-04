#pragma once

#include "TableOfSymbols.h"
#include "AST.h"

namespace clc::prs
{
    using TableOfSymbolsT = 
        TableOfSymbols<std::wstring, std::size_t>;

    class Parser
    {
    private:
        using Priority = char;

        std::stack<Token> stackValue;

        Token pastToken;
        Priority currentPriority = 0;
        Priority GetPriority(Token);

        std::queue<Token> ShuntingYard(std::queue<Token> );

        TableOfSymbolsT tableOfSymbol;

    public:
        AST GetAST(std::queue<Token> );
        TableOfSymbolsT & GetTableOfSymbols();
    };

    inline TableOfSymbolsT & Parser::GetTableOfSymbols()
    {
        return tableOfSymbol;
    }
}