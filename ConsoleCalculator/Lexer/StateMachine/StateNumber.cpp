#include "StateNumber.h"
#include <cwctype>

using namespace clc::lxr;
using namespace clc;

/*
    <---State machine behavior model--->

    1. State::DigitA
        1. If Signal::Digit jump to State::DigitDotExponent.
        2. Any other signal jump to State::Fail.

    2. State::DigitDotExponent
        1. If Signal::Digit jump to State::DigitDotExponent.
        2. If Signal::Dot jump to State::DigitExponent.
        3. If Signal::Exponent jump to State::DigitOperation.
        4. Any other signal jump in State::Good.

    3. State::DigitExponent
        1. If Signal::Digit jump to State::DigitExponent.
        2. If Signal::Exponent jump to State::DigitOperation.
        3. Any other signal jump to State::Good.

    4. State::DigitOperation
        1. If Signal::Digit jump to State::DigitC.
        2. If Signal::Operation jump to State::DigitB.
        3. Any other signal jump to State::Fail.

    5. State::DigitB
        1. If Signal::Digit jump to State::DigitC.
        2. Any other signal jump to State::Fail.

    6. State::DigitC
        1. If Signal::Digit jump to State::DigitC.
        2. Any other signal jump to State::Good.

    7. State::Good
        1. Any other signal jump to State::Fail.

    8. State::Fail
        1. Any other signal jump to State::Fail.
*/

const StateNumber::State StateNumber::jumpTable[][sizeTable]
{
 // Signal::Digit            Signal::Dot,          Signal::Exponent,      Signal::Operation,     Signal::NoMatch,
    State::DigitDotExponent, State::Fail,          State::Fail,           State::Fail,           State::Fail,      // State::DigitA
    State::DigitDotExponent, State::DigitExponent, State::DigitOperation, State::Good,           State::Good,      // State::DigitDotExponent
    State::DigitExponent,    State::Good,          State::DigitOperation, State::Good,           State::Good,      // State::DigitExponent
    State::DigitC,           State::Fail,          State::Fail,           State::DigitB,         State::Fail,      // State::DigitOperation
    State::DigitC,           State::Fail,          State::Fail,           State::Fail,           State::Fail,      // State::DigitB
    State::DigitC,           State::Good,          State::Good,           State::Good,           State::Good,      // State::DigitC
    State::Fail,             State::Fail,          State::Fail,           State::Fail,           State::Fail,      // State::Good
    State::Fail,             State::Fail,          State::Fail,           State::Fail,           State::Fail,      // State::Fail
};

StateNumber::Signal StateNumber::ConvertToSignal(CharType message)
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

StateType StateNumber::Set(CharType message)
{
    ArraySizeType base   = ConvertStateToIndex(currentState);
    ArraySizeType offset = ConvertSignalToIndex(ConvertToSignal(message) );

    currentState = jumpTable[base][offset];

    switch (currentState)
    {
    case State::Good:
        SetStateType(StateType::Number);
        break;

    case State::Fail:
        SetStateType(StateType::Bad);
        break;
    }

    return GetStateType();
}