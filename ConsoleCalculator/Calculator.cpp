#include "Calculator.h"

#include "Parser/ExceptionBadSequence.h"
#include "Parser/ExceptionBadTokens.h"

#include "Exception.h"

using namespace clc;

double Calculator::GetResult()
{
    std::queue<prs::lxr::Token> rpn{};

    try
    {
        rpn = parser.GetRPN();
    }
    catch (prs::ExceptionBadSequence & e)
    {
        throw Exception{e, tableOfSymbols};
    } 
    catch (prs::ExceptionBadTokens & e)
    {
        throw Exception{e, tableOfSymbols};
    }  
    catch (prs::ExceptionParser & e)
    {
        throw Exception{e};
    }  

    std::stack<double> buffer;

    prs::lxr::Token t;
    double l, r;

    while (!rpn.empty() )
    {
        t = rpn.front();
        rpn.pop();

        if (t.type == prs::lxr::Number)
            buffer.push(GetNumber(t) );
        else
        {
            r = buffer.top();
            buffer.pop();

            l = buffer.top();
            buffer.pop();

            switch (t.type)
            {
                case prs::lxr::Multiplication:
                    buffer.push(l * r);
                    break;

                case prs::lxr::Division:
                    buffer.push(l / r);
                    break;

                case prs::lxr::Addition:
                    buffer.push(l + r);
                    break;

                case prs::lxr::Subtraction:
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