#include "JumpTableName.h"
#include <cwctype>

using namespace clc::lxr;
using namespace clc;

const JumpTableName::JumpTable<JumpTableName::State> JumpTableName::jumpTable
{
  // Signal::Digit      Signal::Alpha      Signal::NoMatch
    {State::Fail,       State::DigitAlpha, State::Fail},   // State::Start
    {State::DigitAlpha, State::DigitAlpha, State::Good},   // State::DigitAlpha
    {State::Fail,       State::Fail,       State::Fail},   // State::Good
    {State::Fail,       State::Fail,       State::Fail},   // State::Fail
    
};

JumpTableName::Signal JumpTableName::ConvertToSignal(CharType message)
{   
    if (std::iswdigit(message) )                  return Signal::Digit;
    if (std::iswalpha(message) || message == '_') return Signal::Alpha;

    return Signal::NoMatch;
}

