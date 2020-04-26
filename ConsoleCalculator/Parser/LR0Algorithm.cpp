#include "LR0Algorithm.h"
#include "ExceptionParser.h"

using namespace clc::prs;
using namespace lxr;

std::queue<Token> & LR0Algorithm::GetRPN()
{
    ss.push(Start);
    tb = qt.front();

    Command * currentCommand = commandTable[ss.top() ][tb.type];

    while (currentCommand != &r1)
    {
        currentCommand->Execute();
        currentCommand = commandTable[ss.top() ][tb.type];
    }

    qt.pop();
    return rpn;
}

// Expression -> Expression + Term | Expression - Term

void LR0Algorithm::RC2::Execute()
{
    host.ss.pop();
    host.st.pop();

    host.rpn.push(host.st.top() );

    for (std::size_t i = 0; i < rs; ++i)
    {
        host.ss.pop();
        host.st.pop();
    }

    host.tb.type = Expression;
}

// Expression -> Term

void LR0Algorithm::RC3::Execute()
{
    host.ss.pop();
    host.st.pop();

    host.tb.type = Expression;
}

// Term -> Term * Factor | Term / Factor

void LR0Algorithm::RC4::Execute()
{
    host.ss.pop();
    host.st.pop();

    host.rpn.push(host.st.top() );

    for (std::size_t i = 0; i < rs; ++i)
    {
        host.ss.pop();
        host.st.pop();
    }

    host.tb.type = Term;
}

// Term -> Factor

void LR0Algorithm::RC5::Execute()
{
    host.ss.pop();
    host.st.pop();

    host.tb.type = Term;
}

// Factor -> Number

void LR0Algorithm::RC6::Execute()
{
    host.rpn.push(host.st.top() );

    host.ss.pop();
    host.st.pop();
            
    host.tb.type = lxr::Factor;
}

// Factor -> -Number

void LR0Algorithm::RC7::Execute()
{
    host.ss.pop();
    host.st.pop();
    host.ss.pop();
    host.st.pop();
            
    host.tb.type = lxr::Factor;
}

// Factor -> (Expression)  

void LR0Algorithm::RC8::Execute()
{
    for (std::size_t i = 0; i < rs; ++i)
    {
        host.ss.pop();
        host.st.pop();
    }
            
    host.tb.type = lxr::Factor;
}


void LR0Algorithm::Shift::Execute()
{
    host.ss.push(st);
    host.st.push(host.tb);

    host.qt.pop();
    host.tb = host.qt.front();
}

void LR0Algorithm::Goto::Execute()
{
    host.ss.push(st);
    host.st.push(host.tb);

    host.tb = host.qt.front();
}