#pragma once
#include "Exception.h"

namespace clc
{
    class ExceptionLexer : public Exception
    {
    private:
        std::wstring åxceptionLexerMessage;

    public:
        explicit ExceptionLexer(std::wstring);
        virtual const std::wstring & GetMessage(
            std::wstring addMessage = std::wstring{} ) override;
    };

    inline ExceptionLexer::ExceptionLexer(std::wstring s) :
        åxceptionLexerMessage{L"Lexer."} {}

    inline const std::wstring & ExceptionLexer::GetMessage(
        std::wstring addMessage)
    {
        return Exception::GetMessage() +
            åxceptionLexerMessage + addMessage;
    }
}