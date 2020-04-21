#pragma once

#include <cstddef>

#include <queue>
#include <stack>

#include "ParseTree.h"

/*********************Context-free grammar*********************

    Finish     -> Expression
    Expression -> Expression + Term
    Expression -> Expression - Term
    Expression -> Term

    Term -> Term * Factor
    Term -> Term / Factor
    Term -> Factor

    Factor -> Number
    Factor -> -Number

    Factor -> (Expression)
**************************************************************/

namespace clc::prs
{
    class LR0Algorithm
    {
    private:
        struct Command
        {
            virtual ~Command() {}
            virtual void Execute() = 0;
        };

        enum State : std::size_t // (used in action table)
        {
            Start, A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, E1, F1
        };

        enum ReduceType
        {
            R1,    // Finish     -> Expression
            R2,    // Expression -> Expression + Term | Expression - Term
            R3,    // Expression -> Term
            R4,    // Term       -> Term * Factor | Term / Factor
            R5,    // Term       -> Factor
            R6,    // Factor     -> Number
            R7,    // Factor     -> -Number
            R8,    // Factor     -> (Expression)
        };

        class ShiftCommand : public Command
        {
        private:
            State st;   
            LR0Algorithm & host;     // holder
            bool nf;                // next flag

        public:
            ShiftCommand(State s, LR0Algorithm & h, bool f = false) :
                st{s}, host{h}, nf{f} {}

            virtual void Execute() override;
        };

        class ReduceCommand : public Command
        {
        private:
            ReduceType rt;                     // reduction type
            const std::size_t rs = 3;          // reduction size
            LR0Algorithm & host;               // holder

        public:
            ReduceCommand(ReduceType r, LR0Algorithm & h) :
                rt{r}, host{h} {}

            virtual void Execute() override;
        };

    public:
        LR0Algorithm(std::queue<lxr::Token> & q) : qt{q} {}

        Node * GetTree();

    private:
        std::stack<State> ss;
        std::stack<lxr::Token> st;

        std::stack<Node *> sn;

        std::queue<lxr::Token> & qt;
        lxr::Token tb;   // token buffer

        ReduceCommand r1{R1, *this};   // Finish     -> Expression
        ReduceCommand r2{R2, *this};   // Expression -> Expression + Term | Expression - Term
        ReduceCommand r3{R3, *this};   // Expression -> Term
        ReduceCommand r4{R4, *this};   // Term       -> Term * Factor | Term / Factor
        ReduceCommand r5{R5, *this};   // Term       -> Factor
        ReduceCommand r6{R6, *this};   // Factor     -> Number
        ReduceCommand r7{R7, *this};   // Factor     -> -Number
        ReduceCommand r8{R8, *this};   // Factor     -> (Expression)

        ShiftCommand sA1{A1, *this};
        ShiftCommand sA2{A2, *this, true};
        ShiftCommand sA3{A3, *this};
        ShiftCommand sB1{B1, *this};
        ShiftCommand sB2{B2, *this, true};
        ShiftCommand sB3{B3, *this};
        ShiftCommand sC1{C1, *this, true};
        ShiftCommand sC2{C2, *this};
        ShiftCommand sC3{C3, *this, true};
        ShiftCommand sD1{D1, *this};
        ShiftCommand sD2{D2, *this};
        ShiftCommand sE1{E1, *this};
        ShiftCommand sF1{F1, *this, true};

        Command * commandTable[14][13]
        {
           // Expression Term    Factor Number  Name Call Multiplication Division Addition Subtraction LeftParenthesis RightParenthesis End
            { &sA1,      &sB1,   &sE1,  &sF1,   0,   0,   0,             0,       0,       0,          &sC1,           0,               0,   },    /*START*/
            { 0,         0,      0,     0,      0,   0,   0,             0,       &sA2,    &sA2,       0,              0,               &r1, },    /*A1*/
            { 0,         &sA3,   &sE1,  &sF1,   0,   0,   0,             0,       0,       0,          &sC1,           0,               0,   },    /*A2*/
            { 0,         0,      0,     0,      0,   0,   &sB2,          &sB2,    &r2,     &r2,        0,              &r2,             &r2, },    /*A3*/
            { 0,         0,      0,     0,      0,   0,   &sB2,          &sB2,    &r3,     &r3,        0,              &r3,             &r3, },    /*B1*/
            { 0,         0,      &sB3,  &sF1,   0,   0,   0,             0,       0,       0,          &sC1,           0,               0,   },    /*B2*/
            { 0,         0,      0,     0,      0,   0,   &r4,           &r4,     &r4,     &r4,        0,              0,               &r4, },    /*B3*/
            { &sC2,      &sB1,   &sE1,  &sF1,   0,   0,   0,             0,       0,       0,          &sC1,           0,               0,   },    /*C1*/
            { 0,         0,      0,     0,      0,   0,   0,             0,       &sA2,    &sA2,       0,              &sC3,            0,   },    /*C2*/
            { 0,         0,      0,     0,      0,   0,   &r8,           &r8,     &r8,     &r8,        0,              &r8,             &r8, },    /*C3*/
            { 0,         0,      0,     0,      0,   0,   0,             0,       0,       0,          0,              0,               0,   },    /*D1*/
            { 0,         0,      0,     0,      0,   0,   0,             0,       0,       0,          0,              0,               0,   },    /*D2*/
            { 0,         0,      0,     0,      0,   0,   &r5,           &r5,     &r5,     &r5,        0,              &r5,             &r5, },    /*E1*/
            { 0,         0,      0,     0,      0,   0,   &r6,           &r6,     &r6,     &r6,        0,              &r6,             &r6, },    /*F1*/
        };
    };
}