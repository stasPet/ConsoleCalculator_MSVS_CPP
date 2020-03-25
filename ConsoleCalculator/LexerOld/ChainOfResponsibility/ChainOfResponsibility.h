#pragma once

namespace clc::lxr
{
    class ChainOfResponsibility
    {
    private:
        ChainOfResponsibility * next{};

    public:
        void AddHandler(ChainOfResponsibility *);
        virtual void Handle(wchar_t);
    };

    inline void ChainOfResponsibility::AddHandler(ChainOfResponsibility * n)
    {
        if (next) next->AddHandler(n);
        else next = n;
    }
    inline void ChainOfResponsibility::Handle(wchar_t c)
    {
        next->Handle(c);
    }
}