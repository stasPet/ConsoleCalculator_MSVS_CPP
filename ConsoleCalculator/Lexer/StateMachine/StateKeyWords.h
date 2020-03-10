#pragma once

#include "IState.h"

#include <vector>
#include <list>
#include <string>

namespace clc::lxr
{
    class StateKeyWords : public IState
    {
    private:
        using Predicate = bool(*)(WChar);
        Predicate IsSeparator;

        enum class State: unsigned char
        {
            Check, CheckSeparator, End, Skip
        };

        LexemeType lexemeType;
        LexemeType currentLexemeType;

        State currentState;

        std::vector<WString> operationNames;
        std::list<WString*> pointersToOperationNames;

        std::list<WString>::size_type currentSymbolPosition;

    public:
        StateKeyWords(LexemeType,
                      std::initializer_list<WString>,
                      Predicate);

        LexemeType Set(WChar) override;
        void Reset() override;

        LexemeType GetLexemeType() override;
    };
}