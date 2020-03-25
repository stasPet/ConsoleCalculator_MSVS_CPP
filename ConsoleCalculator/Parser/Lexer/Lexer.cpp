#include <cwctype>
#include "Lexer.h"

#include <iostream>

using namespace clc::prs::lxr;

Token Lexer::GetToken()
{
    std::wstring::value_type wCharBuffer;

    while (*this)
    {
        wCharBuffer = *inputIterator;
        if (!std::iswspace(wCharBuffer) &&
            wCharBuffer != L'\n')
            break;
        else
            ++inputIterator;
    }

    Lexeme currentLexeme;
    std::wstring wStringBuffer;

    if (lexemeBuffer)
        std::swap(lexemeBuffer, currentLexeme);

    while (!currentLexeme)
    {
        wCharBuffer = *inputIterator++;
        lexemeState.SetMessage(wCharBuffer);

        switch (lexemeState.GetState() )
        {
            case LexemeState::Number:
            {
                currentLexeme = Lexeme(TokenEnum::Number, wStringBuffer);

                lexemeBuffer = Lexeme(TokenEnum::Operation,
                    std::wstring(1, wCharBuffer) );
                break;
            }
            case LexemeState::Name:
            {
                currentLexeme = Lexeme(TokenEnum::Name, wStringBuffer);

                lexemeBuffer = Lexeme(TokenEnum::Operation,
                    std::wstring(1, wCharBuffer) );
                break;
            }
            case LexemeState::Fail:
            {
                currentLexeme = Lexeme(TokenEnum::Bad, wStringBuffer);

                lexemeBuffer = Lexeme(TokenEnum::Operation,
                    std::wstring(1, wCharBuffer) );
                break;
            }
            case LexemeState::Operation:
            {
                currentLexeme = Lexeme(TokenEnum::Operation,
                    std::wstring(1, wCharBuffer) );
                break;
            }
            default:
                wStringBuffer += wCharBuffer;
                break;
        }
    }

    pastToken = RefineToken(currentLexeme);
    return pastToken;
}

Token Lexer::RefineToken(Lexeme & l)
{
    switch (l.tokenEnum)
    {
        case TokenEnum::Operation:
            RefineOperation(l);
            break;

        case TokenEnum::Name:
            RefineFunction(l);
            break;
    }

    return Token
    {
        l.tokenEnum,
        tableOfSymbols.SetSymbol(
            std::move(l.wStringValue) ),
    };
}

void Lexer::RefineFunction(Lexeme & l)
{
    for (std::wstring & r : functionNames)
    {
        if (r == l.wStringValue)
        {
            l.tokenEnum = TokenEnum::Function;
            break;
        }
    }
}
void Lexer::RefineOperation(Lexeme & l)
{
    switch (l.wStringValue.front() )
    {
        case L'(':
            l.tokenEnum = TokenEnum::LeftParenthesis;
            break;
        case L')':
            l.tokenEnum = TokenEnum::RightParenthesis;
            break;
        case L';':
            l.tokenEnum = TokenEnum::End;
            break;
    }
}