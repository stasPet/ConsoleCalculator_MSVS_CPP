#pragma once

#include "IState.h"
#include <memory>

// The StateMachine class in turn passes the message to each of its states.

namespace clc::lxr
{
    class StateMachine
    {
    private:

        static constexpr ArraySize size = 4;
        std::unique_ptr<IState> states[size];

        StateType currentState;
        StateType CheckState();

// The method skips all characters until the delimiter is encountered.
        StateType Skip(CharType);

    public:
        StateMachine();

        StateType SetChar(CharType);
        void ResetStates();
    };
}