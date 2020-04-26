#pragma once

#include <cstddef>

#include <queue>
#include <stack>

#include "Lexer/Token.h"

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

        // Finish -> Expression

        class RC1 : public Command
        {
        public:
            RC1() {}
            virtual void Execute() override {}
        };

        // Expression -> Expression + Term | Expression - Term

        class RC2 : public Command
        {
        private:
            const std::size_t rs = 2;   // reduction size
            LR0Algorithm & host;  

        public:
            RC2(LR0Algorithm & h) : host{h} {}
            virtual void Execute() override;
        };

        // Expression -> Term

        class RC3 : public Command
        {
        private:
            LR0Algorithm & host;  

        public:
            RC3(LR0Algorithm & h) : host{h} {}
            virtual void Execute() override;
        };

        // Term -> Term * Factor | Term / Factor

        class RC4 : public Command
        {
        private:
            const std::size_t rs = 2;   // reduction size
            LR0Algorithm & host;  

        public:
            RC4(LR0Algorithm & h) : host{h} {}
            virtual void Execute() override;
        };

        // Term -> Factor

        class RC5 : public Command
        {
        private:
            class LR0Algorithm & host;  

        public:
            RC5(LR0Algorithm & h) : host{h} {}
            virtual void Execute() override;
        };

        // Factor -> Number

        class RC6 : public Command
        {
        private:
            class LR0Algorithm & host;  

        public:
            RC6(LR0Algorithm & h) : host{h} {}
            virtual void Execute() override;
        };

        // Factor -> -Number

        class RC7 : public Command
        {
        private:
            class LR0Algorithm & host;  

        public:
            RC7(LR0Algorithm & h) : host{h} {}
            virtual void Execute() override;
        };

        // Factor -> (Expression)

        class RC8 : public Command
        {
        private:
            const std::size_t rs = 3;   // reduction size
            class LR0Algorithm & host;  

        public:
            RC8(LR0Algorithm & h) : host{h} {}
            virtual void Execute() override;
        };

        enum State : std::size_t // (used in action table)
        {
            Start, A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, E1, F1
        };

        /*
            //
        */

        class Shift : public Command
        {
        private:
            State st;   
            LR0Algorithm & host;

        public:
            Shift(State s, LR0Algorithm & h) : st{s}, host{h} {}

            virtual void Execute() override;
        };

        class Goto : public Command
        {
        private:
            State st;   
            LR0Algorithm & host;

        public:
            Goto(State s, LR0Algorithm & h) : st{s}, host{h} {}

            virtual void Execute() override;
        };

    public:
        LR0Algorithm(std::queue<lxr::Token> & q) : qt{q} {}
        std::queue<lxr::Token> & GetRPN();

    private:
        std::stack<State> ss;           // state service stack
        std::stack<lxr::Token> st;      // token service stack

        std::queue<lxr::Token> rpn;     // output token

        std::queue<lxr::Token> & qt;    // input token
        lxr::Token tb;                  // token buffer

        RC1 r1{};        // Finish     -> Expression

        RC2 r2{*this};   // Expression -> Expression + Term | Expression - Term
        RC3 r3{*this};   // Expression -> Term
        RC4 r4{*this};   // Term       -> Term * Factor | Term / Factor
        RC5 r5{*this};   // Term       -> Factor
        RC6 r6{*this};   // Factor     -> Number
        RC7 r7{*this};   // Factor     -> -Number
        RC8 r8{*this};   // Factor     -> (Expression)

        Goto  sA1{A1, *this};
        Shift sA2{A2, *this};
        Goto  sA3{A3, *this};
        Goto  sB1{B1, *this};
        Shift sB2{B2, *this};
        Goto  sB3{B3, *this};
        Shift sC1{C1, *this};
        Goto  sC2{C2, *this};
        Shift sC3{C3, *this};
        //?  sD1{D1, *this};
        //?  sD2{D2, *this};
        Goto  sE1{E1, *this};
        Shift sF1{F1, *this};

        Command * commandTable[14][13]
        {
           // Expression Term    Factor Number  Name Call Multiplication Division Addition Subtraction LeftParenthesis RightParenthesis End
            { &sA1,      &sB1,   &sE1,  &sF1,   0,   0,   0,             0,       0,       0,          &sC1,           0,               0,   },    /*START*/
            { 0,         0,      0,     0,      0,   0,   0,             0,       &sA2,    &sA2,       0,              0,               &r1, },    /*A1*/
            { 0,         &sA3,   &sE1,  &sF1,   0,   0,   0,             0,       0,       0,          &sC1,           0,               0,   },    /*A2*/
            { 0,         0,      0,     0,      0,   0,   &sB2,          &sB2,    &r2,     &r2,        0,              &r2,             &r2, },    /*A3*/
            { 0,         0,      0,     0,      0,   0,   &sB2,          &sB2,    &r3,     &r3,        0,              &r3,             &r3, },    /*B1*/
            { 0,         0,      &sB3,  &sF1,   0,   0,   0,             0,       0,       0,          &sC1,           0,               0,   },    /*B2*/
            { 0,         0,      0,     0,      0,   0,   &r4,           &r4,     &r4,     &r4,        0,              &r4,             &r4, },    /*B3*/
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