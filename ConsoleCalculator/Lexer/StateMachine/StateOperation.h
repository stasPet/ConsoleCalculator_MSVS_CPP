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
        std::vector<ExpressionStringType>::size_type position;

        TokenType tokenType;
        TokenType currenType;

        std::vector<ExpressionStringType> fNames;
        std::vector<ExpressionStringType*> fNamesRef;

    public:
        StateOperation(TokenType,
            std::initializer_list<ExpressionStringType> );

        TokenType Set(CharType) override;
        void Reset() override;

        TokenType GetTokenType() override;
    };
}