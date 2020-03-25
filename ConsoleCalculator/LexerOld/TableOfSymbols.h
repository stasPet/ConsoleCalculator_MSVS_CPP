#pragma once

#include <initializer_list>
#include <unordered_map>

#include <cstddef>
#include <string>

namespace clc::lxr
{
    template <typename String = std::wstring, 
              typename Attribute = std::size_t>
    class TableOfSymbols
    {
    private:
        std::unordered_map<String, Attribute>
            tableOfSymbolsIn;
        std::unordered_map<Attribute, String>
            tableOfSymbolsOut;

        Attribute valueAttribute = 1;

    public:
        TableOfSymbols() = default;
        TableOfSymbols(std::initializer_list<String> );

        Attribute SetSymbol(String);
        String GetSymbol(Attribute) const;

        void Clear();
    };

    template <typename String, typename Attribute>
    inline void TableOfSymbols<String, Attribute>::Clear()
    {
        tableOfSymbolsIn.clear();
        tableOfSymbolsOut.clear();

        valueAttribute = 1;
    }

    template <typename String, typename Attribute>
    TableOfSymbols<String, Attribute>::TableOfSymbols(std::initializer_list<String> l)
    {
        for (auto it = l.begin(); it != l.end(); ++it)
            SetSymbol(std::move(*it) );
    }

    template <typename String, typename Attribute>
    Attribute TableOfSymbols<String, Attribute>::SetSymbol(String e)
    {
        const auto p = tableOfSymbolsIn.try_emplace(e, valueAttribute);

        if (p.second)
        {
            tableOfSymbolsOut.try_emplace(valueAttribute, std::move(e) );
            return valueAttribute++;
        }

        return p.first->second;
    }
    template <typename String, typename Attribute>
    String TableOfSymbols<String, Attribute>::GetSymbol(Attribute a) const
    {
        auto it = tableOfSymbolsOut.find(a);

        if (it != tableOfSymbolsOut.end() )
            return it->second;

        return String{};
    }
}