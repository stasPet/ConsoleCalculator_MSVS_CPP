#include "StateMachine.h"

#include "StateKeyWords.h"
#include "StateJumpTable.h"

#include "JumpTableNumber.h"
#include "JumpTableName.h"

#include <cwctype>

using namespace clc::lxr;
using namespace clc;

StateMachine::StateMachine(std::initializer_list<LexemeType> l) :
    currentLexemeType{LexemeType::Empty}
{
    if (l.size() == 0)
        throw std::exception{
            "StateMachine::StateMachine \
            (std::initializer_list<LexemeType> )"};

    for (auto & r : l)
        states.emplace_back(IState::Factory(r) );
}

LexemeType StateMachine::SetChar(WChar message)
{
    for (auto & r : states)
        r->Set(message);

    currentLexemeType = CheckState();
    if (currentLexemeType == LexemeType::Bad)
        currentLexemeType = Skip(message);

    return currentLexemeType;
}
void StateMachine::ResetStates()
{
    for (auto & r : states)
        r->Reset();

    currentLexemeType = LexemeType::Empty;
}

LexemeType StateMachine::CheckState()
{
    LexemeType returnLexemeType {};

 // If there is at least one undefined state returned TokenID::NON.
    for (auto const & r : states)
    {
        returnLexemeType = r->GetLexemeType();

        if (returnLexemeType == LexemeType::Empty )
            return returnLexemeType;
    }
        
// If there is at least one correct condition, this state is returned.
    for (auto const & r : states)
    {
        returnLexemeType = r->GetLexemeType();

        if (returnLexemeType != LexemeType::Bad)
            return returnLexemeType;
    }

    return returnLexemeType;
}
LexemeType StateMachine::Skip(WChar message)
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
        return LexemeType::Bad;

    default:
        if (std::iswspace(message) )
            return LexemeType::Bad;
    }

    return LexemeType::Empty;
}