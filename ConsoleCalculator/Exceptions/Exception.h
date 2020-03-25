#pragma once
#include <string>

namespace clc
{
    class Exception
    {
    private:
        std::wstring åxceptionMessage;

    public:
        explicit Exception();
        virtual const std::wstring & GetMessage(
            std::wstring addMessage = std::wstring{} );
    };

    inline Exception::Exception() :
        åxceptionMessage{L"Exception."} {}

    inline const std::wstring & Exception::GetMessage(
        std::wstring addMessage)
    {
        return åxceptionMessage + addMessage;
    }
}