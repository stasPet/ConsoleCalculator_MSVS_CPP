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
        ArraySizeType position;

        static std::vector<ExpressionStringType> fNames;
        std::vector<const ExpressionStringType*> fNamesRef;

    public:

        StateFunction();

        virtual StateType Set(CharType) override;
        virtual void Reset() override;
    };
}