#pragma once

#include <cstddef>

namespace clc::prs::lxr
{
    enum class TokenEnum
    {
        // non-terminals
        Expression,
        Term,
        Factor,
        
        // terminals
        Number,
        Name,
        Operation,
        Function, 
        LeftParenthesis,
        RightParenthesis,
        Bad,
        Empty,
        End
    };

    struct Token
    {
        TokenEnum type;
        std::size_t attribue;

        explicit Token(TokenEnum t = TokenEnum::Empty,
            std::size_t s = 0);

        void Clear();
    };

    inline Token::Token(TokenEnum t, std::size_t s) :
        type(t), attribue(s) {}

    inline void Token::Clear()
    {
        type = TokenEnum::Empty;
        attribue = 0;
    }

    inline bool operator==(Token const & l, Token const & r)
    {
        return l.type == r.type;
    }
    inline bool operator!=(Token const & l, Token const & r)
    {
        return l.type != r.type;
    }
}