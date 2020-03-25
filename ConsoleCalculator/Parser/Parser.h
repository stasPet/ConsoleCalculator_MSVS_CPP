#pragma once

#include "Lexer/Lexer.h"
#include "ParseTree.h"

namespace clc::prs
{
    class Parser
    {
    private:
        lxr::Lexer lexer;

    public:
        Parser(std::wistream &);

        ParseTree GetParseTree();

        lxr::TableOfSymbols<> & GetTableOfSymbol();
    };

    inline Parser::Parser(std::wistream & s) : lexer{s} {}

    inline lxr::TableOfSymbols<> & Parser::GetTableOfSymbol()
    {
        return lexer.GetTableOfSymbol();
    }
}