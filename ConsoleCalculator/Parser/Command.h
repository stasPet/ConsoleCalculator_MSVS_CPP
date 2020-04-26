#pragma once

namespace clc::prs
{
    struct Command
    {
        virtual ~Command() {}
        virtual void Execute() = 0;
    };
}