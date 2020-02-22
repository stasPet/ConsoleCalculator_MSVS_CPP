#pragma once

#include "IState.h"

#include <vector>
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

        State currentState;
        std::vector<String>::size_type position;

        LexemeType lexemeType;
        LexemeType currentLexemeType;

        std::vector<String> fNames;
        std::vector<String*> fNamesRef;

    public:
        StateOperation(LexemeType,
            std::initializer_list<String> );

        LexemeType Set(Char) override;
        void Reset() override;

        LexemeType GetLexemeType() override;
    };
}