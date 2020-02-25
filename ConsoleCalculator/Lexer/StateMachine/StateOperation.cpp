#include "StateOperation.h"

using namespace clc::lxr;
using namespace clc;

StateOperation::StateOperation(LexemeType t,
    std::initializer_list<WString> l) : operationNames{l.size() }
{
    if (l.size() == 0)
        throw std::exception{"StateOperation::StateOperation(TokenType, \
            std::initializer_list<ExpressionStringType> )"};

    auto it = l.begin();
    for (decltype(l.size() ) i = 0; i < l.size(); ++i)
        operationNames[i] = std::move(*it++);

    lexemeType = std::move(t);
    Reset();
}

/*
    Exemple: search "cos"

    message = c          message = o       message = s

    sin   - delete    |                 |               | 
    [c]os - match     | c[o]s - match   | co[s] - match | cos - match
    tg    - delete    |                 |               | 
    [c]tg - match     | c[t]g - delete  |               |
*/

LexemeType StateOperation::Set(WChar message)
{
    switch (currentState)
    {
    case State::Check:
        for (auto p = pointersToOperationNames.begin();
            p != pointersToOperationNames.end(); )
        {
            WString const & element = *(*p);

            if (element[currentSymbolPosition] != message)
                p = pointersToOperationNames.erase(p); 
            else
                ++p;
        }

        if (pointersToOperationNames.size() == 1)
        {
            if (currentSymbolPosition + 1 ==
                pointersToOperationNames.front()->size() )
            {
                currentState = State::SetFlag;
            }
        }
        else if (pointersToOperationNames.empty() )
        {
            currentState = State::Fail;
            currentLexemeType = LexemeType::Bad;
        }

        ++currentSymbolPosition;
        break;

    case State::SetFlag:

        currentState = State::Good;
        currentLexemeType = lexemeType;
        break;

    case State::Good:

        currentState = State::Fail;
        currentLexemeType = LexemeType::Bad;
        break;

    case State::Fail:
        // Skip
        break;
    }

    return currentLexemeType;
}
void StateOperation::Reset()
{
    currentState = State::Check;
    currentLexemeType = LexemeType::Empty;

    pointersToOperationNames.clear();
    for (auto & r : operationNames)
        pointersToOperationNames.push_back(&r);

    currentSymbolPosition = 0;
}

LexemeType StateOperation::GetLexemeType()
{
    return currentLexemeType;
}