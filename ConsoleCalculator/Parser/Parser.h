#pragma once

#include "AST.h"

namespace clc::prs
{
    class Parser
    {
    private:
        AST ast;

    public:
        AST GetAST();
    };
}