#pragma once

#include <istream>
#include <ostream>

#include "../AliasType.h"
#include "TokenType.h"
#include "../TableOfSymbols.h"

namespace clc::lxr
{
    struct Token
    {
        TokenType tokenType = TokenType::Empty;
        AttributeType attributeType = 0;

        void Clear();
    };

    inline void Token::Clear()
    {
        tokenType = TokenType::Empty;
        attributeType = 0;
    }
}