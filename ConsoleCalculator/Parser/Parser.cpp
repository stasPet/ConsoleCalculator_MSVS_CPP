#include "Parser.h"
#include <vector>

using namespace clc::prs;

void Parser::AddToken(Token t)
{
    shuntingYard.AddToken(t);
}

AST Parser::GetAST()
{
    return ast;
}