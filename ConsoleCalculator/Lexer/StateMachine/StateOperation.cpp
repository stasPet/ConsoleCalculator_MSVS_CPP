#include "StateOperation.h"

using namespace clc::lxr;
using namespace clc;

/*
     онструктор принимает строковые значени€, что бы использовать их
    дл€ сравнени€ с вход€щими символами.
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
        ќбъект имеет 4 состо€ни€.
    */
    switch (currentState)
    {
    case State::Check:

        // ѕеребирам по очереди каждую стоку вектора fNamesRef
        for (auto p = fNamesRef.begin(); p != fNamesRef.end(); )
        {
            String const & element = *(*p);

            // ¬ начале position = 0
            if (element[position] != message)
                p = fNamesRef.erase(p); // ≈сли вход€щий символ отсутствует в указанной позиции строки, удал€ем строку из вектора
            else
                ++p;
        }

        if (fNamesRef.size() == 1) // ≈сли в векторе осталась одна строка
        {
            if (position + 1 == (*(fNamesRef.front() ) ).size() ) // “о провер€ем position, если он равен размеру оставшейс€ в векторе строке, значит строка совпала
                currentState = State::SetFlag; // ѕереводим в состо€ние  SetFlag, это нужно что бы пропустить один шаг, 
        }                                      // потому что другие состо€ни€ не могут определить последовательность как коректною,
                                               // если не прочитают следующий за коректной последовательностью символ
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