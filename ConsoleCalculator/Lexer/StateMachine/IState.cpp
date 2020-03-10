#include <cwctype>

#include "IState.h"

#include "StateKeyWords.h"
#include "StateJumpTable.h"

#include "JumpTableNumber.h"
#include "JumpTableName.h"

using namespace clc::lxr;

std::unique_ptr<IState> IState::Factory(LexemeType t)
{
    std::unique_ptr<IState> returnValue;

    switch (t)
    {
        case LexemeType::Number:
        {
            returnValue.reset(new StateJumpTable<JumpTableNumber>
            {
                LexemeType::Number,
                [](WChar c)
                {
                    switch (c)
                    {
                        case L'+': case L'-': case L'*': case L'/':
                        case L')': case L';':
                            return true;

                        default:
                            if (std::iswspace(c) ) return true;
                    }
                
                    return false;
                }
            } );
            break;
        }
        case LexemeType::Name:
        {
            returnValue.reset(new StateJumpTable<JumpTableName>
            {
                LexemeType::Name,
                [](WChar c)
                {
                    switch (c)
                    {
                        case L'+': case L'-': case L'*': case L'/':
                        case L')': case L';':
                            return true;

                        default:
                            if (std::iswspace(c) ) return true;
                    }
                
                    return false;
                }
            } );
            break;
        }
        case LexemeType::Operation:
        {
            returnValue.reset(new StateKeyWords
            {
                LexemeType::Operation,
                {
                    L"*",    L"/",  L"+",   L"-"
                },
                [](WChar c)
                {
                    switch (c)
                    {
                        case L'+': case L'-': case L'(': case L'_':
                            return true;

                        default:
                            if (std::iswspace(c) ||
                                std::iswalnum(c) ) return true;
                    }
                
                    return false;
                }
            } );
            break;
        }
        case LexemeType::Function:
        {
            returnValue.reset(new StateKeyWords
            {
                LexemeType::Function,
                {
                    L"sqrt", L"sin", L"cos", L"ctg", L"tg"
                },
                [](WChar c)
                {
                    if (std::iswspace(c) || c == L'(') return true;
                    return false;
                }
            } );
            break;
        }
        case LexemeType::LeftParenthesis:
        {
            returnValue.reset(new StateKeyWords
            {
                LexemeType::LeftParenthesis, {L"("},
                [](WChar c)
                {
                    switch (c)
                    {
                        case L'+': case L'-': case L'(': case L'_':
                            return true;

                        default:
                            if (std::iswspace(c) ||
                                std::iswalnum(c) ) return true;
                    }
                
                    return false;
                }
            } );
            break;
        }
        case LexemeType::RightParenthesis:
        {
            returnValue.reset(new StateKeyWords
            {
                LexemeType::RightParenthesis, {L")"},
                [](WChar c)
                {
                    switch (c)
                    {
                        case L'+': case L'-': case L'*': case L'/':
                        case L'_': case L';':
                            return true;

                        default:
                            if (std::iswspace(c) ||
                                std::iswalnum(c) ) return true;
                    }
                
                    return false;
                }
            } );
            break;
        }
    }

    return std::move(returnValue);
}