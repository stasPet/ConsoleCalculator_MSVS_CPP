#pragma once

#include "ShuntingYard.h"
#include "AST.h"

namespace clc::prs
{
    class Parser
    {
    private:
        ShuntingYard shuntingYard;
        AST ast;

    public:
        void AddToken(Token);
        AST GetAST();
    };
}