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
            TokenType::Operation,
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
            TokenType::Function,
            {
                L"sqrt", L"sin", L"cos", L"ctg", L"tg"
            }
        }
    );
    states.emplace_back
    (
        new StateOperand<JumpTableNumber>
        {
            TokenType::Operand
        }
    );
    states.emplace_back
    (
        new StateOperand<JumpTableName>
        {
            TokenType::Operand
        }
    );

    currentTokenType = TokenType::Empty;
}

TokenType StateMachine::SetChar(CharType message)
{
    for (auto& r : states)
        r->Set(message);

    currentTokenType = CheckState();
    if (currentTokenType == TokenType::Bad)
        currentTokenType = Skip(message);

    return currentTokenType;
}
void StateMachine::ResetStates()
{
    for (auto& r : states)
        r->Reset();

    currentTokenType = TokenType::Empty;
}

TokenType StateMachine::CheckState()
{
 // If there is at least one undefined state returned TokenID::NON.
    for (const auto& r : states)
        if (r->GetTokenType() == TokenType::Empty )
            return TokenType::Empty;

// If there is at least one correct condition, this state is returned.
    for (const auto& r : states)
        if (r->GetTokenType() != TokenType::Bad)
            return r->GetTokenType();
        /*
        if (r->GetTokenType() != TokenType::Empty &&
            r->GetTokenType() != TokenType::Bad)
                return r->GetTokenType();
        */

    return TokenType::Bad;
}
TokenType StateMachine::Skip(CharType message)
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
        return TokenType::Bad;

    default:
        if (std::iswspace(message) )
            return TokenType::Bad;
    }

    return TokenType::Empty;
}