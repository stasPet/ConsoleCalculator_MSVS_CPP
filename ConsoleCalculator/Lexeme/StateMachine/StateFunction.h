#pragma once

#include "IState.h"
#include <vector>

// TODO later function Set!!!

namespace clc::lxr
{
    class StateFunction: public IState
    {
    private:

        enum class State: unsigned char
        {
            Check, SetFlag, Good, Fail
        };

        State currentState;

        static constexpr ArraySize size = 5;
        ArraySize position;

        std::vector<const ExpressionString*> fNamesRef{size};
        ExpressionString fNames[size];

    public:

        StateFunction();

        virtual StateType Set(CharType) override;
        virtual void Reset() override;
    };
}