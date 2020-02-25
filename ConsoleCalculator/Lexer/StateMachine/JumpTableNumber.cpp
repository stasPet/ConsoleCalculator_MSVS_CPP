#include "JumpTableNumber.h"
#include <cwctype>

using namespace clc::lxr;
using namespace clc;

const JumpTableNumber::JumpTable<JumpTableNumber::State> JumpTableNumber::jumpTable
{
  // Signal::Digit            Signal::Dot           Signal::Exponent         Signal::Operation  Signal::NoMatch
    {State::DigitDotExponent, State::Fail,          State::Fail,             State::Fail,       State::Fail},    // State::Start
    {State::DigitDotExponent, State::DigitExponent, State::DigitOperation,   State::Good,       State::Good},    // State::DigitDotExponent
    {State::DigitExponent,    State::Good,          State::DigitOperation,   State::Good,       State::Good},    // State::DigitExponent
    {State::DigitB,           State::Fail,          State::Fail,             State::DigitA,     State::Fail},    // State::DigitOperation
    {State::DigitB,           State::Fail,          State::Fail,             State::Fail,       State::Fail},    // State::DigitA
    {State::DigitB,           State::Good,          State::Good,             State::Good,       State::Good},    // State::DigitB
    {State::Fail,             State::Fail,          State::Fail,State::Fail, State::Fail,       State::Fail},    // State::Good
    {State::Fail,             State::Fail,          State::Fail,State::Fail, State::Fail,       State::Fail},    // State::Fail
    
};

JumpTableNumber::Signal JumpTableNumber::ConvertToSignal(WChar message)
{   
    switch (message)
    {
        case L'.': return Signal::Dot;

        case L'E':
        case L'e': return Signal::Exponent;

        case L'+':
        case L'-': return Signal::Operation;

        default:
            if (std::iswdigit(message) )
                return Signal::Digit;
    }

    return Signal::NoMatch;
}

