#include <istream>
#include <cwctype>

#include "Lexer.h"

using namespace clc::lxr;

Lexeme Lexer::GetLexeme(std::wistream & stream)
{
    while (stream.get(charBuffer) )
    {
        if (!std::iswspace(charBuffer) &&
            charBuffer != L'\n')
        {
            stream.clear();
            stream.putback(charBuffer);
            break;
        }
    }

    if (stream.get(charBuffer) )
    {
        if (charBuffer == L';')
        {
            currentLexeme.stringValue += L';';
            currentLexeme.typeValue = LexemeType::End;
        }
        else
        {
            stream.clear();
            stream.putback(charBuffer);
        }
    }

    stateMachine.ResetStates();

    while (currentLexeme.typeValue == LexemeType::Empty &&
        stream.get(charBuffer) )
    {
        stringBuffer.push_back(charBuffer);
        currentLexeme.typeValue = stateMachine.SetChar(charBuffer);

        if (currentLexeme.typeValue != LexemeType::Empty)
        {
            stream.clear();
            stream.putback(charBuffer);

            stringBuffer.erase(stringBuffer.end() - 1);

            currentLexeme.stringValue = std::move(stringBuffer);
        }
    }

    return std::move(currentLexeme);
}