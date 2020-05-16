#pragma once

#include <string>
#include "Parser/BadMassage.h"

namespace clc
{
    class Exception
    {
    private:
        std::wstring message;
        bool fatalError;

    public:
        Exception(prs::BadMassage);

        std::wstring GetMessage() {return message;}
        bool IsFatalError() {return fatalError;}
    };
}