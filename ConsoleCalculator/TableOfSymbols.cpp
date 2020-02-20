#include "TableOfSymbols.h"

using namespace clc;

TableOfSymbols::TableOfSymbols(std::initializer_list<ExpressionStringType> l)
{
    for (auto it = l.begin(); it != l.end(); ++it)
        SetSymbol(std::move(*it) );
}

AttributeType TableOfSymbols::SetSymbol(ExpressionStringType e)
{
    const auto p = tableOfSymbolsIn.try_emplace(e, valueAttribute);

    if (p.second)
    {
        tableOfSymbolsOut.try_emplace(valueAttribute, std::move(e) );
        return valueAttribute++;
    }

    return p.first->second;
}
ExpressionStringType TableOfSymbols::GetSymbol(AttributeType a) const
{
    auto it = tableOfSymbolsOut.find(a);

    if (it != tableOfSymbolsOut.end() )
        return it->second;

    return ExpressionStringType{};
}