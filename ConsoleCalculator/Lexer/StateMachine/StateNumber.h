#pragma once

#include "IState.h"
#include <vector>

namespace clc::lxr
{
    class StateNumber: public IState
    {
    private:
        template <typename T> using InternalStateType =
            std::vector<std::vector<T> >;

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
        static const InternalStateType<State> jumpTable;

        static Signal ConvertToSignal(CharType);

        static constexpr ArraySizeType ConvertStateToIndex(State);
        static constexpr ArraySizeType ConvertSignalToIndex(Signal);

    public:

        StateNumber();

        virtual StateType Set(CharType) override;
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

    constexpr ArraySizeType StateNumber::ConvertStateToIndex(State state)
    {
        return static_cast<ArraySizeType>(state);
    }
    constexpr ArraySizeType StateNumber::ConvertSignalToIndex(Signal state)
    {
        return static_cast<ArraySizeType>(state);
    }
}