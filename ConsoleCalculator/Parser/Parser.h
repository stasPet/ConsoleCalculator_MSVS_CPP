#pragma once

#include "Lexer/Lexer.h"
#include <queue>

#include "LR0Algorithm.h"

/*********************Context-free grammar*********************

    Expression -> Expression + Term
    Expression -> Expression - Term
    Expression -> Term

    Term -> Term * Factor
    Term -> Term / Factor
    Term -> Factor

    Factor -> Number
    Factor -> -Number

    Factor -> (Expression)
**************************************************************/

namespace clc::prs
{
    class Parser
    {
    private:
        lxr::Lexer lexer;

        std::queue<lxr::Token> qt;
        LR0Algorithm lroa{qt};

    public:
        Parser(std::wistream &);

        Parser(Parser const &) = delete;
        Parser(Parser &&) = default;

        ~Parser() = default;

        Parser & operator=(Parser const &) = delete;
        Parser & operator=(Parser &&) = default;

        std::queue<lxr::Token> & GetRPN();
        lxr::TableOfSymbols<> & GetTableOfSymbol();
    };

    inline Parser::Parser(std::wistream & s) : lexer{s} {}

    inline lxr::TableOfSymbols<> & Parser::GetTableOfSymbol()
    {
        return lexer.GetTableOfSymbol();
    }
}