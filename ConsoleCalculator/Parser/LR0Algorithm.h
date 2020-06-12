#pragma once

#include <cstddef>

#include <vector>
#include <queue>
#include <stack>
#include <string>

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
        struct Finish : public Command
        {
        public:
            Finish() {}
            virtual void Execute() override {}
        };

        struct Reduce : public Command
        {
        private:
            const lxr::Token rn;        // reduction name
            const std::size_t rs;       // reduction size

            LR0Algorithm & host;  

        public:
            Reduce(LR0Algorithm & h, lxr::Token t, std::size_t s) :
                host{h}, rn{t}, rs{s} {}

            virtual void Execute() override;
        };

        enum State : std::size_t // (used in action table)
        {
            Start,
            A1, A2, A3, B1, B2, B3, C1, C2, C3,
            D1, D2, E1, F1, G1, G2, G3, G4
        };

        class Shift : public Command
        {
        private:
            State state;   
            LR0Algorithm & host;

        public:
            Shift(State s, LR0Algorithm & h) : state{s}, host{h} {}
            virtual void Execute() override;
        };

        class Goto : public Command
        {
        private:
            State state;   
            LR0Algorithm & host;

        public:
            Goto(State s, LR0Algorithm & h) : state{s}, host{h} {}
            virtual void Execute() override;
        };

        class Bad : public Command
        {
        private:
            LR0Algorithm & host;
            std::vector<std::wstring> expectedLexeme;

        public:
            Bad(LR0Algorithm & h,
                std::initializer_list<std::wstring> e)
                    : host{h},
                      expectedLexeme{e} {}

            virtual void Execute() override;
        };

    public:
        LR0Algorithm();

        std::queue<lxr::Token> & GetRPN();
        void PushToken(lxr::Token);

    private:
        std::stack<State> ss;               // state service stack
        std::stack<lxr::Token> st;          // token enum service stack

        std::queue<lxr::Token> rpn;         // output tokens buffer (reverse polish notation)

        std::queue<lxr::Token> qt;          // incoming tokens
        lxr::Token tb;                      // token buffer

        bool IsOperand(lxr::TokenEnum);
        bool IsOperation(lxr::TokenEnum);

        // Finish -> Expression
        Finish r1{};
        
        // Expression -> Expression + Term | Expression - Term
        Reduce r2{*this, lxr::Token{lxr::Expression}, 3};

        // Expression -> Term
        Reduce r3{*this, lxr::Token{lxr::Expression}, 1};

        // Term -> Term * Factor | Term / Factor
        Reduce r4{*this, lxr::Token{lxr::Term}, 3};

        // Term -> Factor
        Reduce r5{*this, lxr::Token{lxr::Term}, 1};

        // Factor -> - Factor
        Reduce r6{*this, lxr::Token{lxr::Factor}, 2};

        // Factor -> Number
        Reduce r7{*this, lxr::Token{lxr::Factor}, 1};

        // Factor -> ( Expression )
        Reduce r8{*this, lxr::Token{lxr::Factor}, 3};

        // Factor -> call ( Expression )
        Reduce r9{*this, lxr::Token{lxr::Factor}, 4};

        Goto  sA1{A1, *this};
        Shift sA2{A2, *this};
        Goto  sA3{A3, *this};

        Goto  sB1{B1, *this};
        Shift sB2{B2, *this};
        Goto  sB3{B3, *this};

        Shift sC1{C1, *this};
        Goto  sC2{C2, *this};
        Shift sC3{C3, *this};

        Shift sD1{D1, *this};
        Goto  sD2{D2, *this};

        Goto  sE1{E1, *this};

        Shift sF1{F1, *this};

        Shift sG1{G1, *this};
        Shift sG2{G2, *this};
        Goto  sG3{G3, *this};
        Shift sG4{G4, *this};


        // Bad handlers TODO

        std::vector<std::vector<Command *> > commandTable;
    };
}