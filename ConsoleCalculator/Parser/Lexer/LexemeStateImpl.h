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

    public:
        void SetMessage(wchar_t);
        State GetState();
    };

    inline void LexemeStateImpl::SetMessage(wchar_t message)
    {
        currentState = jumpTable[currentState][ConvertToSignal(message) ];
    }

    inline LexemeStateImpl::State LexemeStateImpl::GetState()
    {
        return currentState;
    }
}