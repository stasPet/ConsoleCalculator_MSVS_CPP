#pragma once

#include "IState.h"

#include <vector>
#include <list>
#include <string>

namespace clc::lxr
{
    class StateOperation : public IState
    {
    private:
        enum class State: unsigned char
        {
            Check, SetFlag, Good, Fail
        };

        LexemeType lexemeType;
        LexemeType currentLexemeType;

        State currentState;

        std::vector<WString> operationNames;
        std::list<WString*> pointersToOperationNames;

        std::list<WString>::size_type currentSymbolPosition;

    public:
        StateOperation(LexemeType,
            std::initializer_list<WString> );

        LexemeType Set(WChar) override;
        void Reset() override;

        LexemeType GetLexemeType() override;
    };
}