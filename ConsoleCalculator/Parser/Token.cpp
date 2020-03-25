#include "Token.h"

clc::prs::Priority clc::prs::Token::GetPriority()
{
    auto const & t = GetTableOfSymbols();
    auto const & s = t.GetSymbol(attribue);

    Priority retValue{};
    if (!s.empty() )
    {
        
        switch (s.front() )
        {
            case L'*': case L'/': retValue = 2; break;
            case L'+': case L'-': retValue = 1; break;
        }
    }

    return retValue;
}