#include <cwctype>
#include "Lexer.h"

using namespace clc::lxr;

Lexer::Lexer()
{
    cshNumber.AddHandler(&cshName);
    cshNumber.AddHandler(&ch);
}
Token Lexer::GetToken(InputIterator & it)
{
    InputIterator end{};
    while(it != end)
    {
        cshNumber.Handle(*it++);
    }

    return Token{};
}