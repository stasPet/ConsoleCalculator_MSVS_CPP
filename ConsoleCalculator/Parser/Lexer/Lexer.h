#pragma once

#include <istream>
#include <iterator>
#include <string>
#include <forward_list>

#include "Token.h"
#include "LexemeState.h"
#include "TableOfSymbols.h"

namespace clc::prs::lxr
{
    class Lexer
    {
    private:
        LexemeState lexemeState;

        std::istreambuf_iterator<wchar_t> inputIterator;
        std::istreambuf_iterator<wchar_t> endIterator;

        TableOfSymbols<> tableOfSymbols;

        TokenEnum pastToken{Empty};
        bool IsUnary(TokenEnum);

        Token RefineToken(TokenEnum, std::wstring &);

        TokenEnum RefineFunction(std::wstring &);
        TokenEnum RefineOperation(std::wstring::value_type);

        std::forward_list<std::wstring> functionNames;

    public:
        Lexer(std::wistream &, std::initializer_list<std::wstring> l =
                {L"sin", L"cos", L"tan", L"sqrt",} );

        Lexer(Lexer const &) = delete;
        Lexer(Lexer &&) = default;

        ~Lexer() = default;

        Lexer & operator=(Lexer const &) = delete;
        Lexer & operator=(Lexer &&) = default;

        Token GetToken();

        void Reconnect(std::wistream &);
        operator bool();

        TableOfSymbols<> & GetTableOfSymbol();
    };

    inline Lexer::Lexer(std::wistream & i, std::initializer_list<std::wstring> l) :
        inputIterator{i}, functionNames{l} {}

    inline void Lexer::Reconnect(std::wistream & s)
    {
        inputIterator = s;
        tableOfSymbols.Clear();
        pastToken = Empty;
    }

    inline Lexer::operator bool()
    {
        return inputIterator != endIterator;
    }

    inline TableOfSymbols<> & Lexer::GetTableOfSymbol()
    {
        return tableOfSymbols;
    }
}