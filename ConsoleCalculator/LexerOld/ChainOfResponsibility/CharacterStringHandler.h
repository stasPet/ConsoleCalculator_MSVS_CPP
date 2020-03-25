#pragma once

#include <cstddef>
#include "ChainOfResponsibility.h"
#include <iostream>

namespace clc::lxr
{
    template <typename TokenEnum, typename JumpTable>
    class CharacterStringHandler : public ChainOfResponsibility
    {
    private:
        using InternalState = typename JumpTable::State;
        using Signal = typename JumpTable::Signal;

        TokenEnum tokenName;
        InternalState currentState{InternalState::Start};

        static constexpr std::size_t ConvertStateToIndex(InternalState);
        static constexpr std::size_t ConvertSignalToIndex(Signal);

    public:
        CharacterStringHandler(TokenEnum);
        void Handle(wchar_t message);
    };

    template <typename TokenEnum, typename JumpTable>
    inline CharacterStringHandler<TokenEnum, JumpTable>::CharacterStringHandler(
        TokenEnum t) : tokenName{t} {}

    template <typename TokenEnum, typename JumpTable>
    constexpr std::size_t
        CharacterStringHandler<TokenEnum, JumpTable>::ConvertStateToIndex(
            InternalState state)
    {
        return static_cast<std::size_t>(state);
    }
    template <typename TokenEnum, typename JumpTable>
    constexpr std::size_t
        CharacterStringHandler<TokenEnum, JumpTable>::ConvertSignalToIndex(
            Signal signal)
    {
        return static_cast<std::size_t>(signal);
    }

    template <typename TokenEnum, typename JumpTable>
    void CharacterStringHandler<TokenEnum, JumpTable>::Handle(wchar_t message)
    {
        std::size_t base =
            ConvertStateToIndex(currentState);
        std::size_t offset =
            ConvertSignalToIndex(JumpTable::ConvertToSignal(message) );

        currentState = JumpTable::jumpTable[base][offset];

        switch (currentState)
        {
            case InternalState::Start:
            case InternalState::Off:
            {
                ChainOfResponsibility::Handle(message);
                return;
            }
            case InternalState::Good:
            {
                std::wcout << "Handle" << (int)tokenName << " Good: " << message << std::endl;
                ChainOfResponsibility::Handle(message);
                return;
            }
            case InternalState::Fail:
            {
                std::wcout << "Handle" << (int)tokenName << " Good: " << message << std::endl;
                ChainOfResponsibility::Handle(message);
                return;
            }

        }

        std::wcout << "Handle" << (int)tokenName << " :" << message << std::endl;
        return;
    }
}