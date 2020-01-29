#include <istream>
#include <cwctype>

#include "Lexer.h"

using namespace clc::lxr;

Lexeme Lexer::GetLexeme()
{
    Lexeme lexeme;
    CharType bufferChar;

    while (stream.get(bufferChar) )
    {
        if (!std::iswspace(bufferChar) && 
            bufferChar != L'\n' &&
            bufferChar != L';')
        {
            stream.putback(bufferChar);
            break;
        }
    }

    stateMachine.ResetStates();
    lexeme.Clear();

    while (stream.get(bufferChar) )
    {
        lexeme.value.push_back(bufferChar);
        lexeme.type = stateMachine.SetChar(bufferChar);

        if (lexeme.type != StateType::Empty)
        {

            stream.putback(bufferChar);
            lexeme.value.erase(lexeme.value.end() - 1);

            break;
        }
    }

    return lexeme;
}
void Lexer::PutLexeme(Lexeme)
{
    
}