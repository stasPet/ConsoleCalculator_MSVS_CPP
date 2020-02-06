#pragma once

#include <cstddef>
#include <string>

#include "Lexer/Type.h"

namespace clc
{
    using ExpressionStringType = std::wstring;
    using CharType             = std::wstring::value_type;
    using ArraySizeType        = std::size_t;
    using AttributeType        = std::size_t;
    using StateType            = lxr::Type;
    using NumberType           = long double;
}