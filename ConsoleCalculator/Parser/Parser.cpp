#include <stack>
#include "Parser.h"

using namespace clc::prs;
using namespace clc::prs::lxr;

ParseTree Parser::GetParseTree()
{
    lxr::Token currentToken;
    lxr::Token endToken{TokenEnum::End};

    while (lexer)
    {
        currentToken = lexer.GetToken();
        // ...
    }

    return ParseTree{};
}