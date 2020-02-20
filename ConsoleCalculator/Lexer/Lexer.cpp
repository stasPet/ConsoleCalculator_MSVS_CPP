#include <istream>
#include <cwctype>

#include "Lexer.h"

using namespace clc::lxr;

Token Lexer::GetToken()
{
    while (stream.get(charBuffer) )
    {
        if (!std::iswspace(charBuffer) && 
            charBuffer != L'\n' &&
            charBuffer != L';')
        {
            stream.putback(charBuffer);
            break;
        }
    }

    stateMachine.ResetStates();
    stringBuffer.clear();
    currentToken.Clear();

    while (stream.get(charBuffer) )
    {
        stringBuffer.push_back(charBuffer);
        currentToken.tokenType = stateMachine.SetChar(charBuffer);

        if (currentToken.tokenType != TokenType::Empty)
        {

            stream.putback(charBuffer);
            stringBuffer.erase(stringBuffer.end() - 1);

            currentToken.attribue = tableOfSymbols.SetSymbol(stringBuffer);

            break;
        }
    }

    return currentToken;
}
void Lexer::PutToken(Token)
{
    
}