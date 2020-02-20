#include "StateOperation.h"

using namespace clc::lxr;
using namespace clc;

StateOperation::StateOperation(TokenType t,
    std::initializer_list<ExpressionStringType> l)
{
    if (l.size() == 0)
        throw L"StateOperation::StateOperation(TokenType, \
            std::initializer_list<ExpressionStringType> )";

    for (auto& r : l)
        fNames.emplace_back(std::move(r) );

    tokenType = t;
    Reset();
}

TokenType StateOperation::Set(CharType message) 
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
            currenType = TokenType::Bad;
        }
        ++position;
        break;

    case State::SetFlag:
        currentState = State::Good;
        currenType = tokenType;
        break;

    case State::Good:
        currentState = State::Fail;
        currenType = TokenType::Bad;
        break;
    }

    return currenType;
}
void StateOperation::Reset()
{
    currentState = State::Check;
    currenType = TokenType::Empty;

    fNamesRef.resize(fNames.size() );

    for (std::size_t i = 0; i < fNames.size(); ++i)
        fNamesRef[i] = &fNames[i];

    position = 0;
}

TokenType StateOperation::GetTokenType()
{
    return currenType;
}