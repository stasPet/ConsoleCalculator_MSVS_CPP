#pragma once

#include <initializer_list>
#include <unordered_map>

#include "AliasType.h"

namespace clc
{
    class TableOfSymbols
    {
    private:
        std::unordered_map<ExpressionStringType, AttributeType>
            tableOfSymbolsIn;
        std::unordered_map<AttributeType, ExpressionStringType>
            tableOfSymbolsOut;

        AttributeType valueAttribute = 1;

    public:
        TableOfSymbols() = default;
        TableOfSymbols(std::initializer_list<ExpressionStringType> );

        AttributeType SetSymbol(ExpressionStringType);
        ExpressionStringType GetSymbol(AttributeType) const;

        void Clear();
    };

    inline void TableOfSymbols::Clear()
    {
        tableOfSymbolsIn.clear();
        tableOfSymbolsOut.clear();

        valueAttribute = 1;
    }
}