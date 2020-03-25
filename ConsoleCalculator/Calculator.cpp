#include "Calculator.h"

#include <istream>
#include <iterator>
#include <forward_list>

using namespace clc;

std::wstring_view Calculator::GetResult()
{
    prs::ParseTree parseTree = parser.GetParseTree();
    return L"";
}