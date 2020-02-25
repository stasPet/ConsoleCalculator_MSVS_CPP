#pragma once

#include <cstddef>
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

        LexemeType lexemeType;
        LexemeType currentLexemeType;

        static constexpr std::size_t ConvertStateToIndex(State);
        static constexpr std::size_t ConvertSignalToIndex(Signal);

    public:

        StateOperand(LexemeType);

        LexemeType Set(WChar) override;
        void Reset() override;

        LexemeType GetLexemeType() override;
    };

    template <typename JumpTable>
    inline StateOperand<JumpTable>::StateOperand(LexemeType t)
    {
        lexemeType = t;
        Reset();
    }

    template <typename JumpTable>
    inline void StateOperand<JumpTable>::Reset()
    {
        currentState = State::Start;
        currentLexemeType = LexemeType::Empty;
    }

    template <typename JumpTable>
    constexpr std::size_t
        StateOperand<JumpTable>::ConvertStateToIndex(State state)
    {
        return static_cast<std::size_t>(state);
    }
    template <typename JumpTable>
    constexpr std::size_t
        StateOperand<JumpTable>::ConvertSignalToIndex(Signal state)
    {
        return static_cast<std::size_t>(state);
    }

    template <typename JumpTable>
    LexemeType StateOperand<JumpTable>::Set(WChar message)
    {
        std::size_t base   = ConvertStateToIndex(currentState);
        std::size_t offset = ConvertSignalToIndex(JumpTable::ConvertToSignal(message) );

        currentState = JumpTable::jumpTable[base][offset];

        switch (currentState)
        {
            case State::Good:
                currentLexemeType = lexemeType;
                break;

            case State::Fail:
                currentLexemeType = LexemeType::Bad;
                break;
        }

        return currentLexemeType;
    }

    template <typename JumpTable>
    LexemeType StateOperand<JumpTable>::GetLexemeType()
    {
        return currentLexemeType;
    }
}