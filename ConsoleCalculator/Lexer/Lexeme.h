#pragma once
#include <string>

namespace clc::lxr
{
    using Char = std::wstring::value_type;
    using String = std::wstring;

    enum class LexemeType
    {
        Operand, Operation, Function, Bad, Empty
    };

    struct Lexeme
    {
        String stringValue;
        LexemeType typeValue = LexemeType::Empty;
    };
}