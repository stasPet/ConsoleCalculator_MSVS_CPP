#include "StateOperation.h"

using namespace clc::lxr;
using namespace clc;

StateOperation::StateOperation(LexemeType t,
    std::initializer_list<String> l)
{
    if (l.size() == 0)
        throw L"StateOperation::StateOperation(TokenType, \
            std::initializer_list<ExpressionStringType> )";

    for (auto& r : l)
        fNames.emplace_back(std::move(r) );

    lexemeType = t;
    Reset();
}

LexemeType StateOperation::Set(Char message) 
{
    switch (currentState)
    {
    case State::Check:

        for (auto p = fNamesRef.begin(); p != fNamesRef.end(); )
        {
            String const & element = *(*p);

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
            currentLexemeType = LexemeType::Bad;
        }
        ++position;
        break;

    case State::SetFlag:
        currentState = State::Good;
        currentLexemeType = lexemeType;
        break;

    case State::Good:
        currentState = State::Fail;
        currentLexemeType = LexemeType::Bad;
        break;
    }

    return currentLexemeType;
}
void StateOperation::Reset()
{
    currentState = State::Check;
    currentLexemeType = LexemeType::Empty;

    fNamesRef.resize(fNames.size() );

    for (std::size_t i = 0; i < fNames.size(); ++i)
        fNamesRef[i] = &fNames[i];

    position = 0;
}

LexemeType StateOperation::GetLexemeType()
{
    return currentLexemeType;
}