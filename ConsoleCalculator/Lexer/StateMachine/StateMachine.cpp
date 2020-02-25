#include "StateMachine.h"

#include "StateOperation.h"
#include "StateOperand.h"

#include "JumpTableNumber.h"
#include "JumpTableName.h"

#include <cwctype>

using namespace clc::lxr;
using namespace clc;

StateMachine::StateMachine()
{
    states.emplace_back
    (
        new StateOperation
        {
            LexemeType::Operation,
            {
                L"*",    L"/",   L"+",   L"-",
            }
        }
    );
    states.emplace_back
    (
        new StateOperation
        {
            LexemeType::LeftParenthesis, {L"("}
        }
    );
    states.emplace_back
    (
        new StateOperation
        {
            LexemeType::RightParenthesis, {L")"}
        }
    );
    states.emplace_back
    (
        new StateOperation
        {
            LexemeType::Function,
            {
                L"sqrt", L"sin", L"cos", L"ctg", L"tg"
            }
        }
    );
    states.emplace_back
    (
        new StateOperand<JumpTableNumber>
        {
            LexemeType::Operand
        }
    );
    states.emplace_back
    (
        new StateOperand<JumpTableName>
        {
            LexemeType::Operand
        }
    );

    currentLexemeType = LexemeType::Empty;
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