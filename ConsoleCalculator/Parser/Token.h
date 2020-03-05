#pragma once
#include <cstddef>

namespace clc::prs
{
    enum class TokenType
    {
        Operand,         Operation,        Function, 
        LeftParenthesis, RightParenthesis, Bad,      Empty,
        End
    };

    struct Token
    {
        TokenType tokenType;
        std::size_t attribue;

        Token(TokenType t = TokenType::Empty, std::size_t s = 0);

        void Clear();
    };

    inline Token::Token(TokenType t, std::size_t s) : tokenType{t}, attribue{s}
    {
        // ...
    }

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