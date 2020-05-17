#pragma once

#include <string>

#include "Parser/ExceptionBadSequence.h"
#include "Parser/ExceptionBadTokens.h"

#include "Parser/Lexer/TableOfSymbols.h"

namespace clc
{
    class Exception
    {
    private:
        std::wstring message;
        bool fatalError{};

    public:
        Exception(
            prs::ExceptionBadSequence,
            prs::lxr::TableOfSymbols<> &);

        Exception(
            prs::ExceptionBadTokens,
            prs::lxr::TableOfSymbols<> &);

        Exception(prs::ExceptionParser);

        std::wstring GetMessage() {return message;}
        bool IsFatalError() {return fatalError;}
    };
}