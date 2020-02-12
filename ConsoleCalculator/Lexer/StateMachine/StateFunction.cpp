#include "StateFunction.h"

using namespace clc::lxr;
using namespace clc;

std::vector<ExpressionStringType>  StateFunction::fNames
{
    {L"sqrt("}, {L"sin("}, {L"cos("}, {L"ctg("}, {L"tg("}
};

StateFunction::StateFunction()
{
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

    for (std::size_t i = 0; i < fNames.size(); ++i)
        fNamesRef.emplace_back(&fNames[i] );

    position = 0;
}