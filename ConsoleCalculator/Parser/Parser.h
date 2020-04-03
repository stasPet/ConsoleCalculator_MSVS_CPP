#pragma once

#include <stack>
#include <vector>

#include "Lexer/Lexer.h"
#include "ParseTree.h"

/*********************Context-free grammar*********************

    Expression -> Expression + Term
    Expression -> Expression - Term

    Expression -> Term
    Expression -> e

    Term -> Term * Factor
    Term -> Term / Factor
    Term -> Factor

    Factor -> Number
    Factor -> (Expression)
**************************************************************/

namespace clc::prs
{
    class Parser
    {
    private:
        lxr::Lexer lexer;

        enum class Action {accepted, error, shift, reduce};

        std::stack<lxr::Token> stack;

        std::vector<std::vector<Action> > actionsTable;
        std::vector<std::vector<lxr::TokenEnum> > productions;

    public:
        Parser(std::wistream &);

        Parser(Parser const &) = delete;
        Parser(Parser &&) = default;

        ~Parser() = default;

        Parser & operator=(Parser const &) = delete;
        Parser & operator=(Parser &&) = default;

        ParseTree GetParseTree();
        lxr::TableOfSymbols<> & GetTableOfSymbol();
    };

    inline Parser::Parser(std::wistream & s) : lexer{s} {}

    inline lxr::TableOfSymbols<> & Parser::GetTableOfSymbol()
    {
        return lexer.GetTableOfSymbol();
    }
}