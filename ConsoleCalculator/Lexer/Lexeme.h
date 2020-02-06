#pragma once

#include <istream>
#include <ostream>

#include "../AliasType.h"
#include "Type.h"

namespace clc::lxr
{
    struct Lexeme
    {
        Type type = Type::Empty;
        ExpressionStringType value;

        void Clear();
    };

    inline void Lexeme::Clear()
    {
        type = Type::Empty;
        value.clear();
    }

    std::wistream& operator>>(std::wistream&, Lexeme&);
    std::wostream& operator<<(std::wostream&, const Lexeme&);
}