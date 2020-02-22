#include "Parser.h"
#include <vector>

using namespace clc::prs;


AST Parser::GetAST()
{
    std::vector<Token> v;

    Token buffer;
    Token end;

    while (true)
    {
        //buffer = lexer.GetToken();
        v.push_back(buffer);

        if (buffer == end)
            break;
    }

    return ast;
}