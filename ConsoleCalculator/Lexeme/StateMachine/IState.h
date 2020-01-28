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

        virtual const StateType& Set(const CharType&) = 0;
        virtual void Reset() = 0;

        const StateType& GetStateType();
        void SetStateType(const StateType&);
    };

    inline const StateType& IState::GetStateType()
    {
        return stateType;
    }
    inline void IState::SetStateType(const StateType& type)
    {
        stateType = type;
    }
}