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

        static constexpr ArraySize size = 6;
        ArraySize position;

        CharType temp;
        CharType opNames[size];

    public:

        StateOperation();

        virtual const StateType& Set(const CharType&) override;
        virtual void Reset() override;
    };

    inline void StateOperation::Reset()
    {
        currentState = State::Check;
        SetStateType(StateType::Empty);
        temp = 0;
    }
}