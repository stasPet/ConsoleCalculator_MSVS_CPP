#include "ShuntingYard.h"

using namespace clc::prs;

std::queue<Token> ShuntingYard::Transform(
    std::queue<Token> tokenBuffer, TableOfSymbolsT & table)
{
    std::queue<Token> tokenBufferOut;
    while (!tokenBuffer.empty() )
    {
        auto token = tokenBuffer.front();
        tokenBuffer.pop();

        switch (token.tokenType)
        {
            case TokenType::Operand:
                tokenBufferOut.push(token);
                break;

            case TokenType::Operation:
                while (!stackValue.empty() )
                {
                    if(GetPriority(stackValue.top(), table) >=
                        GetPriority(token, table) )
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

ShuntingYard::Priority ShuntingYard::GetPriority(
    Token token, TableOfSymbolsT & table)
{
    auto c = table.GetSymbol(token.attribue).front();

    char p{};

    switch (c)
    {
        case L'*': case L'/': p = 2; break;
        case L'+': case L'-': p = 1; break;
    }

    return p + currentPriority;
}