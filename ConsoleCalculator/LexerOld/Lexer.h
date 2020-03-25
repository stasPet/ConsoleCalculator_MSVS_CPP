#pragma once

#include <istream>

#include "ChainOfResponsibility/CharacterHandler.h"
#include "ChainOfResponsibility/CharacterStringHandler.h"

#include "ChainOfResponsibility/JumpTableName.h"
#include "ChainOfResponsibility/JumpTableNumber.h"

#include "Token.h"

namespace clc::lxr
{
    using InputIterator =
        std::istreambuf_iterator<wchar_t>;

    class Lexer
    {
    private:
        CharacterStringHandler<TokenEnum, JumpTableNumber> cshNumber{TokenEnum::Number};
        CharacterStringHandler<TokenEnum, JumpTableName> cshName{TokenEnum::Name};
        CharacterHandler ch;

    public:
        Lexer();
        Token GetToken(InputIterator &);
    };
}