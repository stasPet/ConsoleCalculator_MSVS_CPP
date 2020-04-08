#pragma once

#include <cstddef>

namespace clc::prs::lxr
{
    enum TokenEnum
    {
        Expression,
        Addition,
        Number,

        // non-terminals
        Term,
        Factor,
        
        // terminals   
        Name,
        Call,
        Bad,
        Multiplication,
        Division,
        Subtraction, 
        LeftParenthesis,
        RightParenthesis, 
        Empty,
        End,

        Operation,
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