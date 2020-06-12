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

    Token returnToken;
    std::wstring wStringBuffer;

    while (inputIterator != endIterator &&
           returnToken.type == TokenEnum::Empty)
    {
        wCharBuffer = *inputIterator;
        lexemeState.SetMessage(wCharBuffer);

        switch (lexemeState.GetState() )
        {
            case LexemeState::Number:
            {
                returnToken = RefineToken(TokenEnum::Number, wStringBuffer);
                break;
            }
            case LexemeState::Name:
            {
                returnToken = RefineToken(TokenEnum::Name, wStringBuffer);
                break;
            }
            case LexemeState::Fail:
            {
                returnToken = RefineToken(TokenEnum::Bad, wStringBuffer);
                break;
            }
            case LexemeState::Operation:
            {
                std::wstring temp{wCharBuffer};
                returnToken = RefineToken(TokenEnum::Operation, temp);
                ++inputIterator;
                break;
            }
            default:
                wStringBuffer += wCharBuffer;
                ++inputIterator;
                break;
        }
    }

    return returnToken;
}

Token Lexer::RefineToken(TokenEnum e, std::wstring & s)
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

    if (IsUnary(e) )
        e = Not;

    pastToken = e;

    return Token
    {
        e, tableOfSymbols.SetSymbol(std::move(s) )
    };
}

TokenEnum Lexer::RefineFunction(std::wstring & s)
{
    for (std::wstring & r : functionNames)
    {
        if (r == s)
            return TokenEnum::Call;
    }

    return TokenEnum::Name;
}
TokenEnum Lexer::RefineOperation(std::wstring::value_type c)
{
    switch (c)
    {
        case L'*':
            return TokenEnum::Multiplication;

        case L'/':
            return TokenEnum::Division;

        case L'+':
            return TokenEnum::Addition;

        case L'-':
            return TokenEnum::Subtraction;

        case L'(':
            return TokenEnum::LeftParenthesis;

        case L')':
            return TokenEnum::RightParenthesis;

        case L';': case L'\n':
            return TokenEnum::End;
    }

    return TokenEnum::Operation;
}