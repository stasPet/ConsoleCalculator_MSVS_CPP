#pragma once
#include <vector>

namespace clc::lxr
{
    struct JumpTableName
    {
        template <typename T> using JumpTable =
            std::vector<std::vector<T> >;

        enum class State: unsigned char
        {
            Start, DigitAlpha, Skip, Off, Good, Fail
        };

        enum class Signal : unsigned char
        {
            Digit, Alpha, Separator, NoMatch
        };

        static const JumpTable<State> jumpTable;
        static Signal ConvertToSignal(wchar_t);
    };
}