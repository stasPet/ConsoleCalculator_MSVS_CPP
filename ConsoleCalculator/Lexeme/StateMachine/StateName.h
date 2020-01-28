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

        static constexpr std::size_t size = 3;
        static const State jumpTable[][size];

        static Signal ConvertToSignal(const CharType&);

        static constexpr ArraySize ConvertStateToIndex(State);
        static constexpr ArraySize ConvertSignalToIndex(Signal);

    public:

        StateName();

        virtual const StateType& Set(const CharType&) override;
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

    constexpr ArraySize StateName::ConvertStateToIndex(State state)
    {
        return static_cast<ArraySize>(state);
    }
    constexpr ArraySize StateName::ConvertSignalToIndex(Signal state)
    {
        return static_cast<ArraySize>(state);
    }
}