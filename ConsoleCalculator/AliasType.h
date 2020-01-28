#pragma once

#include <cstddef>
#include <string>

#include "Lexeme/Type.h"

namespace clc
{
    using ExpressionString = std::wstring;
    using CharType         = std::wstring::value_type;
    using ArraySize        = std::size_t;
    using StateType        = lxr::Type;
}