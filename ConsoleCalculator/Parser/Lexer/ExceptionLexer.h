#pragma once
#include <stack>
#include <string>

#include "Token.h"

namespace clc::prs::lxr
{
    class ExceptionLexer
    {
    private:
        std::wstring exceptionMessage;

    public:
        ExceptionLexer(std::wstring/*, std::stack<Token>*/ );
        const std::wstring & GetMessage();
    };

    inline ExceptionLexer::ExceptionLexer(std::wstring addMessage
        /*, std::stack<Token>*/ ) : exceptionMessage{std::move(addMessage) } {}

    inline const std::wstring & ExceptionLexer::GetMessage()
    {
        return exceptionMessage;
    }
}