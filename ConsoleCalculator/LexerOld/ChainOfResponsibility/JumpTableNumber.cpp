#include "JumpTableNumber.h"
#include <cwctype>

using namespace clc::lxr;
using namespace clc;

const JumpTableNumber::JumpTable<JumpTableNumber::State> JumpTableNumber::jumpTable
{
  // Signal::Digit            Signal::Dot           Signal::Exponent         Signal::Operation  Signal::Separator  Signal::NoMatch
    {State::DigitDotExponent, State::Skip,          State::Off,              State::Start,      State::Start,      State::Off},     // State::Start
    {State::DigitDotExponent, State::DigitExponent, State::DigitOperation,   State::Good,       State::Good,       State::Skip},    // State::DigitDotExponent
    {State::DigitExponent,    State::Good,          State::DigitOperation,   State::Good,       State::Good,       State::Skip},    // State::DigitExponent
    {State::DigitB,           State::Skip,          State::Skip,             State::DigitA,     State::Skip,       State::Skip},    // State::DigitOperation
    {State::DigitB,           State::Skip,          State::Skip,             State::Skip,       State::Skip,       State::Skip},    // State::DigitA
    {State::DigitB,           State::Good,          State::Good,             State::Good,       State::Good,       State::Skip},    // State::DigitB
    {State::Skip,             State::Skip,          State::Skip,             State::Fail,       State::Fail,       State::Skip},    // State::Skip
    {State::Off,              State::Off,           State::Off,              State::Start,      State::Start,      State::Off},     // State::Off
    {State::Start,            State::Start,         State::Start,            State::Start,      State::Start,      State::Start},   // State::Good
    {State::Start,            State::Start,         State::Start,            State::Start,      State::Start,      State::Start},   // State::Fail
    
};

JumpTableNumber::Signal JumpTableNumber::ConvertToSignal(wchar_t message)
{   
    switch (message)
    {
        case L'.': return Signal::Dot;

        case L'E':
        case L'e': return Signal::Exponent;

        case L'+':
        case L'-': return Signal::Operation;

        case L'*': case L'/': case L'(': case L')': case L';':
            return Signal::Separator;

        default:
            if (std::iswdigit(message) ) return Signal::Digit;
            if (std::iswspace(message) ) return Signal::Separator;
    }

    return Signal::NoMatch;
}

