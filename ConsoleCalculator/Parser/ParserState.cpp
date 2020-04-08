#include "ParserState.h"

using namespace clc::prs;
using namespace clc::prs::lxr;

/*
    State | Expectation token
    
*/

const std::size_t ParserState::stats[][3]
{
 // Expression Number Addition
    0,         0,     2,
    2,         0,     2,
    0,         0,     2,
};

ParserState::ParserState()
{
    
}