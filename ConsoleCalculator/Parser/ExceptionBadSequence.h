#pragma once

#include <vector>
#include <string>

#include "ExceptionParser.h"
#include "Lexer/Token.h"

namespace clc::prs
{
    class ExceptionBadSequence : public ExceptionParser
    {
    private:
        lxr::Token token;
        std::vector<std::wstring> expectedLexeme;

    public:
        ExceptionBadSequence(
            std::wstring m,
            lxr::Token t,
            std::vector<std::wstring> e)
                : ExceptionParser{m},
                  token{t},
                  expectedLexeme{e} {}

        lxr::Token GetToken() {return token;}

        std::vector<std::wstring> GetExcpectedLexeme()
        {
            return expectedLexeme;
        }
    };
}