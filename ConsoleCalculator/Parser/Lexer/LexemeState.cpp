#include "LexemeStateImpl.h"
#include "LexemeState.h"

using namespace clc::prs::lxr;

LexemeState::LexemeState() : pImpl(new LexemeStateImpl() ) {}
LexemeState::~LexemeState() {}

LexemeState::StateEnum LexemeState::SetMessage(wchar_t message)
{
    pImpl->SetMessage(message);
    return GetState();
}
LexemeState::StateEnum LexemeState::GetState()
{
    switch (pImpl->GetState() )
    {
        case LexemeStateImpl::Number:    return Number;
        case LexemeStateImpl::Name:      return Name;
        case LexemeStateImpl::Operation: return Operation;
        case LexemeStateImpl::Fail:      return Fail;
    }

    return None;
}
void LexemeState::Reset()
{
    pImpl->SetMessage(L';');
}