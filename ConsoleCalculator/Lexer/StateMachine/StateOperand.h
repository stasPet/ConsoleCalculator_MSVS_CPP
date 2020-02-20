#pragma once

#include "IState.h"

namespace clc::lxr
{
    template <typename JumpTable>
    class StateOperand : public IState
    {
    private:
        using State  = typename JumpTable::State;
        using Signal = typename JumpTable::Signal;

        State currentState;

        TokenType tokenType;
        TokenType currentToken;

        static constexpr ArraySizeType ConvertStateToIndex(State);
        static constexpr ArraySizeType ConvertSignalToIndex(Signal);

    public:

        StateOperand(TokenType);

        TokenType Set(CharType) override;
        void Reset() override;

        TokenType GetTokenType() override;
    };

    template <typename JumpTable>
    inline StateOperand<JumpTable>::StateOperand(TokenType t)
    {
        tokenType = t;
        Reset();
    }

    template <typename JumpTable>
    inline void StateOperand<JumpTable>::Reset()
    {
        currentState = State::Start;
        currentToken = TokenType::Empty;
    }

    template <typename JumpTable>
    constexpr ArraySizeType
        StateOperand<JumpTable>::ConvertStateToIndex(State state)
    {
        return static_cast<ArraySizeType>(state);
    }
    template <typename JumpTable>
    constexpr ArraySizeType
        StateOperand<JumpTable>::ConvertSignalToIndex(Signal state)
    {
        return static_cast<ArraySizeType>(state);
    }

    template <typename JumpTable>
    TokenType StateOperand<JumpTable>::Set(CharType message)
    {
        ArraySizeType base   = ConvertStateToIndex(currentState);
        ArraySizeType offset = ConvertSignalToIndex(JumpTable::ConvertToSignal(message) );

        currentState = JumpTable::jumpTable[base][offset];

        switch (currentState)
        {
            case State::Good:
                currentToken = tokenType;
                break;

            case State::Fail:
                currentToken = TokenType::Bad;
                break;
        }

        return currentToken;
    }

    template <typename JumpTable>
    TokenType StateOperand<JumpTable>::GetTokenType()
    {
        return currentToken;
    }
}