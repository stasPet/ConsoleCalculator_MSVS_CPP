#include "StateOperation.h"

using namespace clc::lxr;
using namespace clc;

StateOperation::StateOperation()
{
    opNames[0] = L'+';
    opNames[1] = L'-';
    opNames[2] = L'*';
    opNames[3] = L'/';
    opNames[4] = L'(';
    opNames[5] = L')';

    Reset();
}

const StateType& StateOperation::Set(const CharType& message)
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