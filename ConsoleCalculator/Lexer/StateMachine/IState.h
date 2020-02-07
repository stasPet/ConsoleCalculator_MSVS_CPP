#pragma once
#include "../../AliasType.h"

namespace clc::lxr
{
    class IState
    {
    private:
        StateType stateType = StateType::Empty;

    public:
        virtual ~IState() {}

        virtual StateType Set(CharType) = 0;
        virtual void Reset() = 0;

        StateType GetStateType() const;
        void SetStateType(StateType);
    };

    inline StateType IState::GetStateType() const
    {
        return stateType;
    }
    inline void IState::SetStateType(StateType type)
    {
        stateType = type;
    }
}