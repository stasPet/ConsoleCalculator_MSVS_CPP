#include "Exception.h"

using namespace clc;

Exception::Exception(
    prs::ExceptionBadSequence e,
    prs::lxr::TableOfSymbols<> & t)
        : message{e.GetMessage() }
{
    message += L" Detected '";
    message += t.GetSymbol(e.GetToken().attribue);
    message += L"', expected";

    for (const auto & r : e.GetExcpectedLexeme() )
    {
        message += L" '";
        message += r;
        message += L"',";
    }

    message.back() = L'.';
}

Exception::Exception(
    prs::ExceptionBadTokens e,
    prs::lxr::TableOfSymbols<> & t)
        : message{e.GetMessage() }
{
    auto badTokens = e.GetBadTokens();

    for (const auto & r : badTokens)
    {
        message += L'\'';
        message += t.GetSymbol(r.attribue);
        message += L"',";
    }

    message.back() = L'.';
}

Exception::Exception(prs::ExceptionParser e)
    : message{e.GetMessage() }
{
    fatalError = true;
}