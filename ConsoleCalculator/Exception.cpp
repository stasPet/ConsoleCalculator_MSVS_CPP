#include "Exception.h"

using namespace clc;
using namespace prs;

Exception::Exception(BadMassage badMessage)
{
    switch (badMessage.GetErrorCode() )
    {
        case 0:
        {
            message = L"Unknown error.";
            fatalError = true;
        }
            break;

        case 1:
        {
            message = L"LR0Algorithm: empty input sequence.";
            fatalError = true;
        }
            break;

        case 2:
        {
            message = L"LR0Algorithm: the sequence must end with ';'.";
            fatalError = true;
        }
            break;

        case 3:
        {
            message = L"LR0Algorithm: bad sequence detected, after:";
            fatalError = true;
        }
            break;

        case 4:
        {
            message = L"Parser: bad token detected:";
            fatalError = true;
        }
            break;
    }
}