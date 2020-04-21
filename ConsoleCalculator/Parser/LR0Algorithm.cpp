#include "LR0Algorithm.h"
#include "ExceptionParser.h"

using namespace clc::prs;

Node * LR0Algorithm::GetTree()
{
    ss.push(Start);
    tb = qt.front();

    Command * currentCommand = commandTable[ss.top() ][tb.type];

    while (currentCommand != &r1)
    {
        currentCommand->Execute();
        currentCommand = commandTable[ss.top() ][tb.type];
    }

    Node * returnNode = nullptr;
    if (!st.empty() )
    {
        returnNode = sn.top();
        sn.pop();
    }

    return returnNode;
}

void LR0Algorithm::LR0Algorithm::ShiftCommand::Execute()
{
    host.ss.push(st);
    host.st.push(host.tb);

    if (nf) host.qt.pop();
    host.tb = host.qt.front();
}

void LR0Algorithm::LR0Algorithm::ReduceCommand::Execute()
{
    switch (rt)
    {
        case R1:
        {
            /*
                Finish -> Expression
                Unreachable code!
            */
        }
            break;
        case R2:
        {
            // Expression -> Expression + Term | Expression - Term

            host.ss.pop();
            host.st.pop();

            Node * n = new Node(host.st.top() );

            n->rn = host.sn.top();
            host.sn.pop();

            n->ln = host.sn.top();
            host.sn.pop();

            host.sn.push(n);

            for (std::size_t i = 0; i < 2; ++i)
            {
                host.ss.pop();
                host.st.pop();
            }

            host.tb.type = lxr::Expression;
        }
            break;
        case R3:
        {
            // Expression -> Term
            host.ss.pop();
            host.st.pop();

            host.tb.type = lxr::Expression;
        }
            break;
        case R4:
        {
            // Term -> Term * Factor | Term / Factor

            host.ss.pop();
            host.st.pop();

            Node * n = new Node(host.st.top() );

            n->rn = host.sn.top();
            host.sn.pop();

            n->ln = host.sn.top();
            host.sn.pop();

            host.sn.push(n);

            for (std::size_t i = 0; i < 2; ++i)
            {
                host.ss.pop();
                host.st.pop();
            }

            host.tb.type = lxr::Term;
        }
            break;
        case R5:
        {
            // Term -> Factor

            host.ss.pop();
            host.st.pop();

            host.tb.type = lxr::Term;
        }
            break;
        case R6:
        {
            // Factor -> Number

            host.sn.push(new Node(host.st.top() ) );

            host.ss.pop();
            host.st.pop();
            
            host.tb.type = lxr::Factor;
        }
            break;
        case R7:
        {
            // Factor -> -Number

            host.ss.pop();
            host.st.pop();
            host.ss.pop();
            host.st.pop();
            
            host.tb.type = lxr::Factor;
        }
            break;
        case R8:
        {
            // Factor -> (Expression)  
            for (std::size_t i = 0; i < rs; ++i)
            {
                host.ss.pop();
                host.st.pop();
            }
            
            host.tb.type = lxr::Factor;
        }
            break;
    }
}
