#pragma once

#include "IState.h"
#include <vector>


namespace clc::lxr
{
    class StateOperation: public IState
    {
    private:

        enum class State: unsigned char
        {
            Check, SetFlag, Good, Fail
        };

        State currentState;

        static constexpr ArraySizeType size = 6;
        ArraySizeType position;

        CharType temp;
        CharType opNames[size];

    public:

        StateOperation();

        virtual StateType Set(CharType) override;
        virtual void Reset() override;
    };

    inline void StateOperation::Reset()
    {
        currentState = State::Check;
        SetStateType(StateType::Empty);
        temp = 0;
    }
}