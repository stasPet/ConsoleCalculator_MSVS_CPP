#include "StateName.h"
#include <cwctype>

using namespace clc::lxr;
using namespace clc;

/*
    <---State machine behavior model--->

    1. S1
        1. If ALP jump to S2.
        2. Any other signal jump to S4.

    2. S2
        1. If ALP jump to S2.
        2. If DIG jump to S2.
        3. If SEP jump to S3.

    3. S3
        1. Any other signal jump to S4.

    4. S4
        1. Any other signal jump to S4.
*/

const StateName::InternalStateType<StateName::State> StateName::jumpTable
{
 // Signal::Alpha      Signal::Digit      Signal::NoMath
    {State::DigitAlpha, State::Fail,       State::Fail},   // State::Alpha
    {State::DigitAlpha, State::DigitAlpha, State::Good},   // State::DigitAlpha
    {State::Fail,       State::Fail,       State::Fail},   // State::Good
    {State::Fail,       State::Fail,       State::Fail},   // State::Fail
};

StateName::Signal StateName::ConvertToSignal(CharType message)
{
    if (std::iswalpha(message) || message == '_') return Signal::Alpha;
    if (std::iswdigit(message) )                  return Signal::Digit;

    return Signal::NoMath;
}

StateType StateName::Set(CharType message)
{
    ArraySizeType base   = ConvertStateToIndex(currentState);
    ArraySizeType offset = ConvertSignalToIndex(ConvertToSignal(message) );

    currentState = jumpTable[base][offset];

    switch (currentState)
    {
    case State::Good:
        SetStateType(StateType::Name);
        break;

    case State::Fail:
        SetStateType(StateType::Bad);
        break;
    }

    return GetStateType();
}