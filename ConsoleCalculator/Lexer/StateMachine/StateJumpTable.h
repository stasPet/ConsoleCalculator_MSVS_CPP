#pragma once

#include <cstddef>
#include "IState.h"

namespace clc::lxr
{
    template <typename JumpTable>
    class StateJumpTable : public IState
    {
    private:
        using State  = typename JumpTable::State;
        using Signal = typename JumpTable::Signal;

        using Predicate = bool(*)(WChar);
        Predicate IsSeparator;

        State currentState;

        LexemeType lexemeType;
        LexemeType currentLexemeType;

        static constexpr std::size_t ConvertStateToIndex(State);
        static constexpr std::size_t ConvertSignalToIndex(Signal);

    public:
        StateJumpTable(LexemeType, Predicate);

        LexemeType Set(WChar) override;
        void Reset() override;

        LexemeType GetLexemeType() override;
    };

    template <typename JumpTable>
    inline StateJumpTable<JumpTable>::StateJumpTable(LexemeType t,
        Predicate p) : lexemeType{t}, IsSeparator{p}
    {
        Reset();
    }

    template <typename JumpTable>
    inline void StateJumpTable<JumpTable>::Reset()
    {
        currentState = State::Start;
        currentLexemeType = LexemeType::Empty;
    }

    template <typename JumpTable>
    constexpr std::size_t
        StateJumpTable<JumpTable>::ConvertStateToIndex(State state)
    {
        return static_cast<std::size_t>(state);
    }
    template <typename JumpTable>
    constexpr std::size_t
        StateJumpTable<JumpTable>::ConvertSignalToIndex(Signal state)
    {
        return static_cast<std::size_t>(state);
    }

    template <typename JumpTable>
    LexemeType StateJumpTable<JumpTable>::Set(WChar message)
    {
        std::size_t base =
            ConvertStateToIndex(currentState);
        std::size_t offset =
            ConvertSignalToIndex(JumpTable::ConvertToSignal(message) );

        currentState = JumpTable::jumpTable[base][offset];

        switch (currentState)
        {
            case State::Good:
                if (IsSeparator(message) )
                    currentLexemeType = lexemeType;          
                break;

            case State::Fail:
                currentLexemeType = LexemeType::Bad;
                break;
        }

        return currentLexemeType;
    }

    template <typename JumpTable>
    LexemeType StateJumpTable<JumpTable>::GetLexemeType()
    {
        return currentLexemeType;
    }
}