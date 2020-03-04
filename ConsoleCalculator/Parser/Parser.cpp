#include "Parser.h"

using namespace clc::prs;

AST Parser::GetAST(std::queue<Token> tokenBuffer)
{
    std::queue<Token> tempBuffer{ShuntingYard(std::move(tokenBuffer) ) };
    return AST{tempBuffer};
}

std::queue<Token> Parser::ShuntingYard(std::queue<Token> tokenBuffer)
{
    
    std::queue<Token> tokenBufferOut;
    while (!tokenBuffer.empty() )
    {
        Token token = tokenBuffer.front();
        tokenBuffer.pop();

        pastToken = token;

        switch (token.tokenType)
        {
            case TokenType::Operand:
                tokenBufferOut.push(token);
                break;

            case TokenType::Operation:
                while (!stackValue.empty() )
                {
                    if(GetPriority(stackValue.top()) >=
                        GetPriority(token) )
                    {
                        tokenBufferOut.push(stackValue.top() );
                        stackValue.pop();
                    }
                    else
                        break;
                }
                stackValue.push(token);
                break;
        }
    }

    while (!stackValue.empty() )
    {
        tokenBufferOut.push(stackValue.top() );
        stackValue.pop();
    }

    return std::move(tokenBufferOut);
}

Parser::Priority Parser::GetPriority(Token token)
{
    auto c = tableOfSymbol.GetSymbol(token.attribue).front();

    

    if (token.tokenType == TokenType::LeftParenthesis)
        ++currentPriority;

    if (token.tokenType == TokenType::RightParenthesis)
        --currentPriority;



    Priority p{};
    switch (c)
    {
        case L'*': case L'/': p = 2; break;
        case L'+': case L'-': p = 1; break;
    }

    return p + currentPriority;
}