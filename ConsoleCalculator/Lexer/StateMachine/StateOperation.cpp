#include "StateOperation.h"

using namespace clc::lxr;
using namespace clc;

/*
    The constructor accepts string values so that they can be used to compare with incoming characters.
*/

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
    /*
        The object has 4 states.
    */
    switch (currentState)
    {
    case State::Check:

        // Iterate through each line of the vector fNamesRef in turn
        for (auto p = fNamesRef.begin(); p != fNamesRef.end(); )
        {
            String const & element = *(*p);

            // At the beginning position = 0
            if (element[position] != message)
                p = fNamesRef.erase(p); // If the input character is not in the specified position of the string, remove the string from the vector
            else
                ++p;
        }

        if (fNamesRef.size() == 1) // f there is one line left in the vector
        {
            if (position + 1 == (*(fNamesRef.front() ) ).size() ) // That we check the position, if it is equal to the size of the row remaining in the vector, then the row coincided
                currentState = State::SetFlag; // We set it to SetFlag state, this is necessary to skip one step,
        }                                      // because other states cannot determine the sequence as correct,
                                               // if they don’t read the character following the correct sequence
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