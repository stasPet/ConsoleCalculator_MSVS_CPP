#pragma once

#include <cstddef>

namespace clc::prs::lxr
{
    enum TokenEnum : std::size_t // (used in action table)
    {
        // non-terminals
        Expression,
        Term,
        Factor,
        
        // terminals   
        Number,
        Name,               // not implemented
        Call,               // not implemented
        Multiplication,
        Division,
        Addition,
        Subtraction,
        UnarySubtraction,   // not implemented
        LeftParenthesis,
        RightParenthesis,  
        End,

        // not used in the parser
        Empty,
        Bad,
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