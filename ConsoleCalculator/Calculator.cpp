#include "Calculator.h"

#include "Parser/BadMassage.h"
#include "Exception.h"

using namespace clc;
using namespace prs;
using namespace lxr;

double Calculator::GetResult()
{
    std::queue<Token> rpn{};

    try
    {
        rpn = parser.GetRPN();
    }
    catch (BadMassage & m)
    {
        throw Exception{m};
    }  

    std::stack<double> buffer;

    Token t;
    double l, r;

    while (!rpn.empty() )
    {
        t = rpn.front();
        rpn.pop();

        if (t.type == Number)
            buffer.push(GetNumber(t) );
        else
        {
            r = buffer.top();
            buffer.pop();

            l = buffer.top();
            buffer.pop();

            switch (t.type)
            {
                case Multiplication:
                    buffer.push(l * r);
                    break;

                case Division:
                    buffer.push(l / r);
                    break;

                case Addition:
                    buffer.push(l + r);
                    break;

                case Subtraction:
                    buffer.push(l - r);
                    break;
            }
        }
    }

    double returnValue{};

    if (!buffer.empty() )
        returnValue = buffer.top();

    return returnValue;
}

double Calculator::GetNumber(prs::lxr::Token t)
{
    return std::stod(tableOfSymbols.GetSymbol(t.attribue) );
}