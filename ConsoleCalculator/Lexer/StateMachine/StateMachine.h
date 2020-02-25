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
        std::vector<std::unique_ptr<IState> > states;

        LexemeType currentLexemeType;
        LexemeType CheckState();

// The method skips all characters until the delimiter is encountered.
        LexemeType Skip(WChar);

    public:
        StateMachine();

        LexemeType SetChar(WChar);
        void ResetStates();
    };
}