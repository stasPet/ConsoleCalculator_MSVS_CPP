#pragma once
#include <string>

namespace clc::prs
{
    class ExceptionParser
    {
    private:
        std::wstring message;

    public:
        ExceptionParser(std::wstring m = L"Unknown error.")
            : message{m} {}

        std::wstring GetMessage() {return message;}
    };
}