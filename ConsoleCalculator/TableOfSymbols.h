#pragma once

#include <initializer_list>
#include <unordered_map>

#include "AliasType.h"

namespace clc
{
    class TableOfSymbols
    {
    private:
        template <typename T1, typename T2> using TableType =
            std::unordered_map<T1, T2>;

        TableType<ExpressionStringType, AttributeType> tableOfSymbolsIn;
        TableType<AttributeType, ExpressionStringType> tableOfSymbolsOut;

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
    }
}