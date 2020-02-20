#pragma once
#include "AliasType.h"

namespace clc::lxr
{
    enum class TokenType
    {
        Operand, Operation, Function, Bad, Empty
    };

    struct Token
    {
        TokenType tokenType = TokenType::Empty;
        AttributeType attribue = 0;

        void Clear();
    };

    inline void Token::Clear()
    {
        tokenType = TokenType::Empty;
        attribue = 0;
    }

    inline bool operator==(Token const & l, Token const & r)
    {
        return l.tokenType == r.tokenType;
    }
    inline bool operator!=(Token const & l, Token const & r)
    {
        return l.tokenType != r.tokenType;
    }
}