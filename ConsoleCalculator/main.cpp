#include <iostream>
#include <sstream>

#include "Calculator.h"
#include "Exception.h"

using namespace clc;

int main()
{
    std::wstring expression{L"2 -(5+-sqrt((1);"};

    std::wistringstream sstream{expression};
    Calculator calculator{sstream};

    std::wcout << expression << std::endl;

    while (calculator)
    {
        try
        {
            std::wcout << calculator.GetResult()
                << std::endl;
        }
        catch(Exception & e)
        {
            std::wcerr << e.GetMessage() << std::endl;

            if (e.IsFatalError() )
                break;
        }
    }

    return 0;
}