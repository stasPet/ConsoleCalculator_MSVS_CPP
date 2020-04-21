#pragma once

#include <stack>
#include <string>

namespace clc::prs
{
    class ExceptionParser
    {
    private:
        std::wstring exceptionMessage;

    public:
        ExceptionParser(std::wstring/*, std::stack<Token>*/ );
        const std::wstring & GetMessage();
    };

    inline ExceptionParser::ExceptionParser(std::wstring addMessage
        /*, std::stack<Token>*/ ) : exceptionMessage{std::move(addMessage) } {}

    inline const std::wstring & ExceptionParser::GetMessage()
    {
        return exceptionMessage;
    }
}