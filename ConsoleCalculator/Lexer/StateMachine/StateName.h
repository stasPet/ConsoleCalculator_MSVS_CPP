#pragma once
#include "IState.h"

namespace clc::lxr
{
    class StateName: public IState
    {
    private:

        enum class State: unsigned char
        {
            Alpha, DigitAlpha, Good, Fail,
        };
        enum class Signal: unsigned char {Alpha, Digit, NoMath};

        State currentState;

        static constexpr ArraySizeType size = 3;
        static const State jumpTable[][size];

        static Signal ConvertToSignal(const CharType&);

        static constexpr ArraySizeType ConvertStateToIndex(State);
        static constexpr ArraySizeType ConvertSignalToIndex(Signal);

    public:

        StateName();

        virtual StateType Set(CharType) override;
        virtual void Reset() override;
    };

    inline StateName::StateName()
    {
        Reset();
    }
    inline void StateName::Reset()
    {
        currentState = State::Alpha;
        SetStateType(StateType::Empty);
    }

    constexpr ArraySizeType StateName::ConvertStateToIndex(State state)
    {
        return static_cast<ArraySizeType>(state);
    }
    constexpr ArraySizeType StateName::ConvertSignalToIndex(Signal state)
    {
        return static_cast<ArraySizeType>(state);
    }
}