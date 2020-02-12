#include "StateOperation.h"

using namespace clc::lxr;
using namespace clc;

std::vector<CharType> StateOperation::opNames
{
    L'+', L'-', L'*', L'/', L'(', L')'
};

StateOperation::StateOperation()
{
    Reset();
}

StateType StateOperation::Set(CharType message)
{
    switch (currentState)
    {
    case State::Check:
        for (auto&& w : opNames)
        {
            if(w == message)
            {
                temp = message;
                break;
            }
        }

        if (temp)
            currentState = State::SetFlag;
        else
        {
            currentState = State::Fail;
            SetStateType(StateType::Bad);
        }

        break;

    case State::SetFlag:
        currentState = State::Good;
        SetStateType(StateType::Operation);
        break;

    case State::Good:
        currentState = State::Fail;
        SetStateType(StateType::Bad);
        break;
    }

    return GetStateType();
}