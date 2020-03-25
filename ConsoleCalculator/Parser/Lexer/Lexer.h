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
    using InputIterator = std::istreambuf_iterator<wchar_t>;

    class Lexer
    {
    public:
        struct Lexeme
        {
            TokenEnum tokenEnum;
            std::wstring wStringValue;

            Lexeme(TokenEnum e = TokenEnum::Empty,
                std::wstring s = std::wstring() );
            operator bool();

        };

    private:
        LexemeState lexemeState;

        InputIterator inputIterator;
        InputIterator endIterator;

        Lexeme lexemeBuffer;
        Token pastToken;

        TableOfSymbols<> tableOfSymbols;

        Token RefineToken(Lexeme &);

        void RefineFunction(Lexeme &);
        void RefineOperation(Lexeme &);

        std::forward_list<std::wstring> functionNames;

    public:
        Lexer(std::wistream &, std::initializer_list<std::wstring> l =
                {L"sin", L"cos", L"tg", L"ctg", L"sqrt",} );

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
    }

    inline Lexer::operator bool()
    {
        return inputIterator != endIterator ||
            lexemeBuffer.tokenEnum != TokenEnum::Empty;
    }

    inline TableOfSymbols<> & Lexer::GetTableOfSymbol()
    {
        return tableOfSymbols;
    }

    inline Lexer::Lexeme::Lexeme(TokenEnum e, std::wstring s) :
        tokenEnum(e), wStringValue(s) {}
    inline Lexer::Lexeme::operator bool()
    {
        if (tokenEnum == TokenEnum::Empty) return false;
        return true;
    }
}