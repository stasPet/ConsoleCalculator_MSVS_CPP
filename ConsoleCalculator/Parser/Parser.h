#pragma once

#include "../Lexer/Lexer.h"

namespace clc::psr
{
    class Parser
    {
    private:
        lxr::Lexer lexer;

    public:
        Parser(std::wistream & s): lexer{s} {}


    };
}