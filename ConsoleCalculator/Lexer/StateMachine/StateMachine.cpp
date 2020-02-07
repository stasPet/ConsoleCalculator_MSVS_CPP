#include "StateMachine.h"

#include "StateFunction.h"
#include "StateName.h"
#include "StateNumber.h"
#include "StateOperation.h"

#include <cwctype>

using namespace clc::lxr;
using namespace clc;

StateMachine::StateMachine()
{
    states.emplace_back(new StateFunction{} );
    states.emplace_back(new StateName{} );
    states.emplace_back(new StateNumber{} );
    states.emplace_back(new StateOperation{} );

    currentState = StateType::Empty;
}

StateType StateMachine::SetChar(CharType message)
{
    for (auto& r : states)
        r->Set(message);

    currentState = CheckState();
    if (currentState == StateType::Bad)
        currentState = Skip(message);

    return currentState;
}
void StateMachine::ResetStates()
{
    for (auto&& r : states)
        r->Reset();

    currentState = StateType::Empty;
}

StateType StateMachine::CheckState()
{
 // If there is at least one undefined state returned TokenID::NON.
    for (const auto& r : states)
        if (r->GetStateType() == StateType::Empty)
            return StateType::Empty;

// If there is at least one correct condition, this state is returned.
    for (const auto& r : states)
        if (r->GetStateType() != StateType::Empty &&
            r->GetStateType() != StateType::Bad)
                return r->GetStateType();

    return StateType::Bad;
}
StateType StateMachine::Skip(CharType message)
{
    switch (message)
    {
    case L'*':
    case L'/':
    case L'+':
    case L'-':
    case L';':
    case L'(':
    case L')':
        return StateType::Bad;

    default:
        if (std::iswspace(message) )
            return StateType::Bad;
    }

    return StateType::Empty;
}