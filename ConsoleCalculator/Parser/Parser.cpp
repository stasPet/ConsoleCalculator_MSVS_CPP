#include <queue>

#include "Parser.h"
#include "ExceptionParser.h"

using namespace clc::prs;
using namespace lxr;

ParseTree Parser::GetParseTree()
{
    std::queue<Token> qt;

    while (lexer)
    {
        qt.push(lexer.GetToken() );
        if (qt.back().type == End) break;
    }
    
    if (qt.back().type != End)
        throw ExceptionParser{L"ParseTree Parser::GetParseTree()"};

    LR0Algorithm lroa{qt};
    return lroa.GetTree();
}