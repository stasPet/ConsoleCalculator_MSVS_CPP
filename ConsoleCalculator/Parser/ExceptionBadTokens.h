#pragma once

#include <vector>

#include "ExceptionParser.h"
#include "Lexer/Token.h"

namespace clc::prs
{
    class ExceptionBadTokens : public ExceptionParser
    {
    private:
        std::vector<lxr::Token> badTokens;

    public:
        ExceptionBadTokens(
            std::wstring m,
            std::vector<lxr::Token> b)
                : ExceptionParser{m},
                  badTokens{b} {}

        std::vector<lxr::Token> GetBadTokens() {return badTokens;}
    };
}