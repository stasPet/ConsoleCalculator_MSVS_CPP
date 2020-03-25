#include "JumpTableName.h"
#include <cwctype>

using namespace clc::lxr;

const JumpTableName::JumpTable<JumpTableName::State> JumpTableName::jumpTable
{
  // Signal::Digit      Signal::Alpha      Signal::Separator, Signal::NoMatch
    {State::Off,        State::DigitAlpha, State::Start,      State::Skip},   // State::Start
    {State::DigitAlpha, State::DigitAlpha, State::Good,       State::Skip},   // State::DigitAlpha
    {State::Skip,       State::Skip,       State::Fail,       State::Skip},   // State::Skip
    {State::Skip,       State::Skip,       State::Fail,       State::Skip},   // State::Off
    {State::Start,      State::Start,      State::Start,      State::Start},  // State::Good
    {State::Start,      State::Start,      State::Start,      State::Start},  // State::Fail
    
};

JumpTableName::Signal JumpTableName::ConvertToSignal(wchar_t message)
{   
    switch (message)
    {
        case L'_':
            return Signal::Alpha;

        case L'+': case L'-': case L'*': case L'/':
        case L'(': case L')': case L';':
            return Signal::Separator;

        default:
            if (std::iswspace(message) ) return Signal::Separator;
            if (std::iswdigit(message) ) return Signal::Digit;
            if (std::iswalpha(message) ) return Signal::Alpha;
    } 

    return Signal::NoMatch;
}

