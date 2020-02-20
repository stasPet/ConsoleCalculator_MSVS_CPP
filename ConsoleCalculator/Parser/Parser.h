#pragma once

#include "Lexer/Lexer.h"
#include "AST.h"

namespace clc::prs
{
    class Parser
    {
    private:
        lxr::Lexer lexer;
        AST ast{lxr::Token{} };

    public:
        Parser(std::wistream &, TableOfSymbols &);
        AST GetAST();
    };

    inline Parser::Parser(std::wistream & s, TableOfSymbols & t) :
        lexer{s, t} {}
}