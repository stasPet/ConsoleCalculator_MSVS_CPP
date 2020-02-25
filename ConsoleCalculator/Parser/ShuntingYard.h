#pragma once

#include <list>
#include "Token.h"

namespace clc::prs
{
    class ShuntingYard
    {
    private:
        std::list<Token> listValue;

    public:
        void AddToken(Token);
    };
}