#pragma once

#include <cstddef>

namespace clc::prs::lxr
{
    class LexemeStateImpl
    {
    public:
        enum State
        {
            Start,  DigitDotExponent, DigitExponent, DigitOperation,
            DigitA, DigitB,           DigitAlpha,    Skip,
            Number, Name,             Operation,     Fail
        };

    private:
        enum Signal
        {
            Digit, Dot, Exponent, PlusMinus, Separator, Alpha, NoMatch
        };
 
        State currentState{Start};
        static const State jumpTable[][12];

        static Signal ConvertToSignal(wchar_t);

        static std::size_t ConvertStateToIndex(State);
        static std::size_t ConvertSignalToIndex(Signal);

    public:
        void SetMessage(wchar_t);
        State GetState();
    };

    inline LexemeStateImpl::State LexemeStateImpl::GetState()
    {
        return currentState;
    }

    inline std::size_t LexemeStateImpl::ConvertStateToIndex(State state)
    {
        return static_cast<std::size_t>(state);
    }
    inline std::size_t LexemeStateImpl::ConvertSignalToIndex(Signal signal)
    {
        return static_cast<std::size_t>(signal);
    }
}