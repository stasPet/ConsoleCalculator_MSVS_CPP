#pragma once
#include <string>

namespace clc::lxr
{
    using WChar = std::wstring::value_type;
    using WString = std::wstring;

    enum class LexemeType
    {
        Operand,         Operation,        Function,
        LeftParenthesis, RightParenthesis, Bad,      Empty,
        End
    };

    struct Lexeme
    {
        WString stringValue;
        LexemeType typeValue{LexemeType::Empty};

        Lexeme() = default;
        Lexeme(Lexeme const &) = default;
        Lexeme(Lexeme &&);

        Lexeme& operator=(Lexeme const &) = default;
    };

    inline Lexeme::Lexeme(Lexeme && l) : stringValue{std::move(l.stringValue) },
        typeValue{l.typeValue}
    {
        l.typeValue = LexemeType::Empty;
    }
}