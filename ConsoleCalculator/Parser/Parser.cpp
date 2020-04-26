#include "Parser.h"
#include "ExceptionParser.h"

using namespace clc::prs;
using namespace lxr;

std::queue<lxr::Token> & Parser::GetRPN()
{
    while (lexer)
    {
        qt.push(lexer.GetToken() );
        if (qt.back().type == End) break;
    }
    
    if (qt.empty() )
        throw ExceptionParser{L"ParseTree Parser::GetParseTree()"};

    if (qt.back().type != End)
        throw ExceptionParser{L"ParseTree Parser::GetParseTree()"};

    
    return lroa.GetRPN();
}