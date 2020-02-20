#pragma once

#include "AliasType.h"
#include <vector>

namespace clc::lxr
{
    struct JumpTableName
    {
        template <typename T> using JumpTable =
            std::vector<std::vector<T> >;

        enum class State: unsigned char
        {
            Start, DigitAlpha, Good, Fail
        };

        enum class Signal : unsigned char
        {
            Digit, Alpha, NoMatch
        };

        static const JumpTable<State> jumpTable;
        static Signal ConvertToSignal(CharType);
    };
}