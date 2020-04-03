#include <cwctype>
#include "Lexer.h"

using namespace clc::prs::lxr;

Token Lexer::GetToken()
{
    std::wstring::value_type wCharBuffer;

    while (inputIterator != endIterator)
    {
        wCharBuffer = *inputIterator;
        if (std::iswspace(wCharBuffer) &&
            wCharBuffer != L'\n')
            ++inputIterator;
        else
            break;
    }

    std::wstring wStringBuffer;

    while (inputIterator != endIterator &&
           lexemeBuffer.empty() )
    {
        wCharBuffer = *inputIterator++;
        lexemeState.SetMessage(wCharBuffer);

        switch (lexemeState.GetState() )
        {
            case LexemeState::Number:
            {
                InsertBuffer(TokenEnum::Number, wStringBuffer, wCharBuffer);
                break;
            }
            case LexemeState::Name:
            {
                InsertBuffer(TokenEnum::Name, wStringBuffer, wCharBuffer);
                break;
            }
            case LexemeState::Fail:
            {
                InsertBuffer(TokenEnum::Bad, wStringBuffer, wCharBuffer);
                break;
            }
            case LexemeState::Operation:
            {
                lexemeBuffer.push
                (
                    RefineToken(TokenEnum::Operation,
                        std::wstring{wCharBuffer} ) 
                );
                break;
            }
            default:
                wStringBuffer += wCharBuffer;
                break;
        }
    }

    Token returnToken;
    if (!lexemeBuffer.empty() )
    {
        returnToken = lexemeBuffer.front();
        lexemeBuffer.pop();
    }

    return returnToken;
}

Token Lexer::RefineToken(TokenEnum e, std::wstring s)
{
    switch (e)
    {
        case TokenEnum::Operation:
            e = RefineOperation(s.front() );
            break;

        case TokenEnum::Name:
            e = RefineFunction(s);
            break;
    }

    return Token
    {
        e, tableOfSymbols.SetSymbol(std::move(s) ),
    };
}

TokenEnum Lexer::RefineFunction(std::wstring & s)
{
    for (std::wstring & r : functionNames)
    {
        if (r == s)
            return TokenEnum::Function;
    }

    return TokenEnum::Name;
}
TokenEnum Lexer::RefineOperation(std::wstring::value_type c)
{
    switch (c)
    {
        case L'(':
            return TokenEnum::LeftParenthesis;
        case L')':
            return TokenEnum::RightParenthesis;
        case L';': case L'\n':
            return TokenEnum::End;
    }

    return TokenEnum::Operation;
}