#pragma once

#include <vector>

namespace clc::lxr
{
    struct JumpTableNumber
    {
        template <typename T> using JumpTable =
            std::vector<std::vector<T> >;

        enum class State: unsigned char
        {
            Start,          DigitDotExponent, DigitExponent,
            DigitOperation, DigitA,           DigitB,
            Skip,           Off,
            Good,           Fail
        };

        enum class Signal : unsigned char
        {
            Digit, Dot, Exponent, Operation, Separator, NoMatch
        };


        static const JumpTable<State> jumpTable;
        static Signal ConvertToSignal(wchar_t);
    };
}