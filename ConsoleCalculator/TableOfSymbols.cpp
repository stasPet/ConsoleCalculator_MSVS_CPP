#include "TableOfSymbols.h"

using namespace clc;

TableOfSymbols::TableOfSymbols(std::initializer_list<ExpressionStringType> l)
{
    for (auto it = l.begin(); it != l.end(); ++it)
        SetSymbol(std::move(*it) );
}

AttributeType TableOfSymbols::SetSymbol(ExpressionStringType e)
{
    /*if (tableOfSymbolsIn.find(e) == tableOfSymbolsIn.end() )
    {
        tableOfSymbolsOut[valueAttribute] = e;
        tableOfSymbolsIn[std::move(e) ] = valueAttribute++;
    }*/

    AttributeType& a = tableOfSymbolsIn[e];

    if (!a)
    {
        tableOfSymbolsOut[valueAttribute] = std::move(e);
        a = valueAttribute++;
    }

    return a;
}
ExpressionStringType TableOfSymbols::GetSymbol(AttributeType a) const
{
    auto it = tableOfSymbolsOut.find(a);

    if (it != tableOfSymbolsOut.end() )
        return it->second;

    return ExpressionStringType{};
}