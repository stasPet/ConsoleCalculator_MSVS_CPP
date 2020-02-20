#include "Parser.h"
#include <vector>
#include "Lexer/Token.h"

using namespace clc::prs;
using namespace clc::lxr;

AST Parser::GetAST()
{
    std::vector<Token> v;

    Token buffer;
    Token end;

    while (true)
    {
        buffer = lexer.GetToken();
        v.push_back(buffer);

        if (buffer == end)
            break;
    }

    return ast;
}