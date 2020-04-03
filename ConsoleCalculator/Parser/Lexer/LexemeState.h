#pragma once
#include <memory>

namespace clc::prs::lxr
{
    class LexemeState
    {
    public:
        enum StateEnum
        {
            Number, Name, Operation, Fail, None
        };

        LexemeState();
        
        LexemeState(LexemeState const &) = delete;
        LexemeState(LexemeState &&) = default;

        ~LexemeState();

        LexemeState & operator=(LexemeState const &) = delete;
        LexemeState & operator=(LexemeState &&) = default;

        StateEnum SetMessage(wchar_t);

        StateEnum GetState();
        void Reset();

    private:
        std::unique_ptr<class LexemeStateImpl> pImpl;
    };
}