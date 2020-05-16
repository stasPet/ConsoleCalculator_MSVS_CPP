#pragma once

#include <cstddef>
#include <string>
#include <queue>

#include "Lexer/Token.h"

namespace clc::prs
{
    class BadMassage
    {
    private:
        std::queue<lxr::Token> tokens;
        std::size_t errorCode;

    public:
        BadMassage(
            std::size_t c = 0,
            std::queue<lxr::Token> t = std::queue<lxr::Token>{} )
                : errorCode{c},
                  tokens{std::move(t) } {};

        std::queue<lxr::Token> GetTokens() {return tokens;};
        std::size_t GetErrorCode() {return errorCode;};
    };
}