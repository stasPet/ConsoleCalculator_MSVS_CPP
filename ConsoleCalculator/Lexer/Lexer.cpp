#include <istream>
#include <cwctype>

#include "Lexer.h"

using namespace clc::lxr;

Lexeme Lexer::GetLexeme(std::wistream & stream)
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

    while (stream.get(charBuffer) )
    {
        stringBuffer.push_back(charBuffer);
        currentLexeme.typeValue = stateMachine.SetChar(charBuffer);

        if (currentLexeme.typeValue != LexemeType::Empty)
        {

            stream.putback(charBuffer);
            stringBuffer.erase(stringBuffer.end() - 1);

            currentLexeme.stringValue = std::move(stringBuffer);

            break;
        }
    }

    return std::move(currentLexeme);
}