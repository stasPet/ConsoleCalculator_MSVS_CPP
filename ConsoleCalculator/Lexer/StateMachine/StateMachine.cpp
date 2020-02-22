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
                L"(",    L")",   L";"
            }
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

LexemeType StateMachine::SetChar(Char message)
{
    for (auto& r : states)
        r->Set(message);

    currentLexemeType = CheckState();
    if (currentLexemeType == LexemeType::Bad)
        currentLexemeType = Skip(message);

    return currentLexemeType;
}
void StateMachine::ResetStates()
{
    for (auto& r : states)
        r->Reset();

    currentLexemeType = LexemeType::Empty;
}

LexemeType StateMachine::CheckState()
{
 // If there is at least one undefined state returned TokenID::NON.
    for (const auto& r : states)
        if (r->GetLexemeType() == LexemeType::Empty )
            return LexemeType::Empty;

// If there is at least one correct condition, this state is returned.
    for (const auto& r : states)
        if (r->GetLexemeType() != LexemeType::Bad)
            return r->GetLexemeType();
        /*
        if (r->GetTokenType() != TokenType::Empty &&
            r->GetTokenType() != TokenType::Bad)
                return r->GetTokenType();
        */

    return LexemeType::Bad;
}
LexemeType StateMachine::Skip(Char message)
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