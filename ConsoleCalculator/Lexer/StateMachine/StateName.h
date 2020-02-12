#pragma once

#include "IState.h"
#include <vector>

namespace clc::lxr
{
    class StateName: public IState
    {
    private:
        template <typename T> using InternalStateType =
            std::vector<std::vector<T> >;

        enum class State: unsigned char
        {
            Alpha, DigitAlpha, Good, Fail,
        };
        enum class Signal: unsigned char {Alpha, Digit, NoMath};

        State currentState;
        static const InternalStateType<State> jumpTable;

        static Signal ConvertToSignal(CharType);

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