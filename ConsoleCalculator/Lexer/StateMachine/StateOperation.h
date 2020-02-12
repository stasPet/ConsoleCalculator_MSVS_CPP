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
        ArraySizeType position;

        CharType temp;
        static std::vector<CharType> opNames;

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