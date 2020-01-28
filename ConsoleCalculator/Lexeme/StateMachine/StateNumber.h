#pragma once

#include "IState.h"

namespace clc::lxr
{
    class StateNumber: public IState
    {
    private:
        enum class State: unsigned char
        {
            DigitA, DigitDotExponent, DigitExponent, DigitOperation,
            DigitB, DigitC,           Good,          Fail,
        };

        enum class Signal: unsigned char
        {
            Digit, Dot, Exponent, Operation, NoMatch,
        };

        State currentState;

        static constexpr ArraySize sizeTable {5};
        static const State jumpTable[][sizeTable];

        static Signal ConvertToSignal(const CharType&);

        static constexpr ArraySize ConvertStateToIndex(State);
        static constexpr ArraySize ConvertSignalToIndex(Signal);

    public:

        StateNumber();

        virtual const StateType& Set(const CharType&) override;
        virtual void Reset() override;
    };

    inline StateNumber::StateNumber()
    {
        Reset();
    }
    inline void StateNumber::Reset()
    {
        currentState = State::DigitA;
        SetStateType(StateType::Empty);
    }

    constexpr ArraySize StateNumber::ConvertStateToIndex(State state)
    {
        return static_cast<ArraySize>(state);
    }
    constexpr ArraySize StateNumber::ConvertSignalToIndex(Signal state)
    {
        return static_cast<ArraySize>(state);
    }
}