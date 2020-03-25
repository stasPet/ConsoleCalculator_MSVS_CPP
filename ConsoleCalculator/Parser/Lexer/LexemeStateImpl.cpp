#include "LexemeStateImpl.h"
#include <cwctype>

using namespace clc::prs::lxr;

const LexemeStateImpl::State LexemeStateImpl::jumpTable[][12] =
{
  // Digit             Dot,           Exponent,       PlusMinus, Separator, Alpha       NoMatch
    {DigitDotExponent, Skip,          DigitAlpha,     Operation, Operation, DigitAlpha, Skip},  // State::Start
    {DigitDotExponent, DigitExponent, DigitOperation, Number,    Number,    Skip,       Skip},  // State::DigitDotExponent
    {DigitExponent,    Number,        DigitOperation, Number,    Number,    Number,     Skip},  // State::DigitExponent
    {DigitB,           Fail,          Fail,           DigitA,    Fail,      Fail,       Fail},  // State::DigitOperation
    {DigitB,           Fail,          Fail,           Fail,      Fail,      Fail,       Fail},  // State::DigitA
    {DigitB,           Number,        Number,         Number,    Number,    Number,     Number},// State::DigitB
    {DigitAlpha,       Skip,          DigitAlpha,     Name,      Name,      DigitAlpha, Skip},  // State::DigitAlpha
    {Skip,             Skip,          Skip,           Fail,      Fail,      Skip,       Skip},  // State::Skip
    {DigitDotExponent, Skip,          DigitAlpha,     Operation, Operation, DigitAlpha, Skip},  // State::Number
    {DigitDotExponent, Skip,          DigitAlpha,     Operation, Operation, DigitAlpha, Skip},  // State::Name
    {DigitDotExponent, Skip,          DigitAlpha,     Operation, Operation, DigitAlpha, Skip},  // State::Operation
    {DigitDotExponent, Skip,          DigitAlpha,     Operation, Operation, DigitAlpha, Skip},  // State::Fail
};

LexemeStateImpl::Signal LexemeStateImpl::ConvertToSignal(wchar_t message)
{   
    switch (message)
    {
        case L'.':
            return Dot;

        case L'E':
        case L'e':
            return Exponent;

        case L'+':
        case L'-':
            return PlusMinus;

        case L'*': case L'/':
        case L'(': case L')':
        case L';': case L'\n':
            return Separator;

        default:
            if (std::iswdigit(message) )
                return Digit;
            if (std::iswalpha(message) || message == L'_')
                return Alpha;
            if (std::iswspace(message) )
                return Separator;
    }

    return NoMatch;
}

void LexemeStateImpl::SetMessage(wchar_t message)
{
    std::size_t base   = ConvertStateToIndex(currentState);
    std::size_t offset = ConvertSignalToIndex(ConvertToSignal(message) );

    currentState = jumpTable[base][offset];
}