#pragma once

#include "ChainOfResponsibility.h"

namespace clc::lxr
{
    class CharacterHandler : public ChainOfResponsibility
    {
    public:
        virtual void Handle(wchar_t) override;
    };
}