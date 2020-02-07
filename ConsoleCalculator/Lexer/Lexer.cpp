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
    token.Clear();
    stringBuffer.clear();

    while (stream.get(charBuffer) )
    {
        stringBuffer.push_back(charBuffer);
        token.tokenType = stateMachine.SetChar(charBuffer);

        if (token.tokenType != StateType::Empty)
        {

            stream.putback(charBuffer);
            stringBuffer.erase(stringBuffer.end() - 1);

            token.attributeType = tableOfSymbols.SetSymbol(stringBuffer);

            break;
        }
    }

    return token;
}
void Lexer::PutToken(Token)
{
    
}