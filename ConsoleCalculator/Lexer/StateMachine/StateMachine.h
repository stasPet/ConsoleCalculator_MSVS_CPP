#pragma once

#include "IState.h"

#include <memory>
#include <vector>

// The StateMachine class in turn passes the message to each of its states.

namespace clc::lxr
{
    class StateMachine
    {
    private:
        using StatsType = std::vector<std::unique_ptr<IState> >;
        StatsType states;

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