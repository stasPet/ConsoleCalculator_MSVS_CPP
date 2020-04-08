#pragma once

#include <cstddef>
#include "Lexer/Token.h"

namespace clc::prs
{
    class ParserState
    {
    private:
        static const std::size_t stats[][3];

    public:
        ParserState();
    };
}