#pragma once

#include "AliasType.h"
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
            Good,           Fail
        };

        enum class Signal : unsigned char
        {
            Digit, Dot, Exponent, Operation, NoMatch
        };

        static const JumpTable<State> jumpTable;
        static Signal ConvertToSignal(CharType);
    };
}