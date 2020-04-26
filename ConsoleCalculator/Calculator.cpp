#include "Calculator.h"

using namespace clc;
using namespace prs;
using namespace lxr;

std::wstring Calculator::GetResult()
{
    std::queue<Token> opn = parser.GetRPN();
    std::stack<double> buffer;

    Token t;
    double l, r;

    while (!opn.empty() )
    {
        t = opn.front();
        opn.pop();

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

    return std::to_wstring(buffer.top() );
}

double Calculator::GetNumber(prs::lxr::Token t)
{
    return std::stod(tableOfSymbols.GetSymbol(t.attribue) );
}