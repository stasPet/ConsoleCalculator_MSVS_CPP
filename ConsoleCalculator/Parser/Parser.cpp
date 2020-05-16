#include "Parser.h"
#include "BadMassage.h"

using namespace clc::prs;
using namespace lxr;

std::queue<lxr::Token> & Parser::GetRPN()
{
    Token tempToken{};
    std::queue<lxr::Token> badTokens;

    while (lexer)
    {
        tempToken = lexer.GetToken();

        if (tempToken.type == Bad)
            badTokens.push(tempToken); 
        
        if (badTokens.empty() )
            lroa.PushToken(tempToken);

        if (tempToken.type == End) break;
    }

    // 4 - Parser: bad token detected:
    if (!badTokens.empty() )
        throw BadMassage{4, badTokens};

    return lroa.GetRPN();
}