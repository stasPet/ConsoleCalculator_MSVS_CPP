#include "StateFunction.h"

using namespace clc::lxr;
using namespace clc;

StateFunction::StateFunction()
{
    fNames[0] = L"sqrt(";
    fNames[1] = L"sin(";
    fNames[2] = L"cos(";
    fNames[3] = L"ctg(";
    fNames[4] = L"tg(";

    Reset();
}

StateType StateFunction::Set(CharType message) 
{
    switch (currentState)
    {
    case State::Check:

        for (auto p = fNamesRef.begin(); p != fNamesRef.end(); )
        {
            const ExpressionStringType& element = *(*p);

            if (element[position] != message)
                p = fNamesRef.erase(p);
            else
                ++p;
        }

        if (fNamesRef.size() == 1)
        {
            if (position + 1 == (*(fNamesRef.front() ) ).size() )
                currentState = State::SetFlag;
        }
        else if (fNamesRef.empty() )
        {
            currentState = State::Fail;
            SetStateType(StateType::Bad);
        }

        ++position;
        break;

    case State::SetFlag:
        currentState = State::Good;
        SetStateType(StateType::Function);
        break;

    case State::Good:
        currentState = State::Fail;
        SetStateType(StateType::Bad);
        break;
    }

    return GetStateType();
}
void StateFunction::Reset()
{
    currentState = State::Check;
    SetStateType(StateType::Empty);

    fNamesRef.resize(5);
    for (std::size_t i = 0; i < size; ++i)
        fNamesRef[i] = &fNames[i];

    position = 0;
}