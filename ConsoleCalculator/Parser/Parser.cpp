#include <stack>
#include "Parser.h"

using namespace clc::prs;
using namespace clc::prs::lxr;

/*********************Context-free grammar (Test)******************************

    Finish     -> Expression
    Expression -> Expression + Number
    Expression -> Number

******************************************************************************/

ParseTree Parser::GetParseTree()
{
    // ...

    return ParseTree{};
}