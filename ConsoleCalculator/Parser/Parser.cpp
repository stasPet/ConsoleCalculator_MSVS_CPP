#include "Parser.h"
#include "ExceptionBadTokens.h"

#include <vector>

using namespace clc::prs;
using namespace lxr;

std::queue<lxr::Token> Parser::GetRPN()
{
    LR0Algorithm lroa{};
    std::vector<lxr::Token> badTokens;
    Token tempToken{};

    while (lexer)
    {
        tempToken = lexer.GetToken();

        if (tempToken.type == Bad)
            badTokens.push_back(tempToken); 
        
        if (badTokens.empty() )
            lroa.PushToken(tempToken);

        if (tempToken.type == End)
            break;
    }

    if (!badTokens.empty() )
        throw ExceptionBadTokens{L"Parser: bad token detected:",
            badTokens};

    return lroa.GetRPN();
}