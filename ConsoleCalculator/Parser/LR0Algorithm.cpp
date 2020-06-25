#include "LR0Algorithm.h"
#include "ExceptionBadSequence.h"

#include "ShowStateDebug.h"

using namespace clc::prs;
using namespace lxr;

std::queue<lxr::Token> & LR0Algorithm::GetRPN()
{          
    if (qt.empty() )
        throw ExceptionParser{
            L"LR0Algorithm: empty input sequence."};

    if (qt.back().type != End)
        throw ExceptionParser{
            L"LR0Algorithm: the sequence must end with ';'."};

    ss.push(Start);
    tb = qt.front();

    Command * currentCommand = commandTable[ss.top() ][tb.type];

    while (currentCommand != &r1)
    {
        ShowState( static_cast<DebugState>(ss.top() ) );

        currentCommand->Execute();
        currentCommand = commandTable[ss.top() ][tb.type];
    }

    qt.pop();
    return rpn;
}

void LR0Algorithm::Reduce::Execute()
{
    for (std::size_t i = 0; i < rs; ++i)
    {
        if (IsOperation(host.st.top().type) )
            host.rpn.push(host.st.top() );

        host.ss.pop();
        host.st.pop();
    }

    host.tb = rn;
}

void LR0Algorithm::Shift::Execute()
{
    if (IsOperand(host.tb.type) )
        host.rpn.push(host.tb);

    host.ss.push(state);
    host.st.push(host.tb);

    host.qt.pop();
    host.tb = host.qt.front();
}

void LR0Algorithm::Goto::Execute()
{
    host.ss.push(state);
    host.st.push(host.tb);

    host.tb = host.qt.front();
}

void LR0Algorithm::Bad::Execute()
{
    throw ExceptionBadSequence
    {
        L"LR0Algorithm: Bad sequence.",
        host.tb,
        expectedLexeme
    };
}

void LR0Algorithm::FatalError::Execute()
{
    throw ExceptionParser{};
}

bool LR0Algorithm::Shift::IsOperand(TokenEnum t)
{
    return t == Number || t == Name;
}
bool LR0Algorithm::Reduce::IsOperation(TokenEnum t)
{
    return t == Multiplication ||
           t == Division ||
           t == Addition ||
           t == Subtraction ||
           t == Not ||
           t == Call;
}

void LR0Algorithm::PushToken(lxr::Token t)
{
    qt.push(t);
}

LR0Algorithm::LR0Algorithm() :
    commandTable(18, std::vector<Command *>(14) )
{
    // START
    commandTable[0][0]   = &sA1;       // Expression
    commandTable[0][1]   = &sB1;       // Term
    commandTable[0][2]   = &sE1;       // Factor
    commandTable[0][3]   = &sF1;       // Number
    commandTable[0][4]   = &sF1;       // Name
    commandTable[0][5]   = &sG1;       // Call
    commandTable[0][6]   = &b1;        // Multiplication
    commandTable[0][7]   = &b1;        // Division
    commandTable[0][8]   = &b1;        // Addition
    commandTable[0][9]   = &b1;        // Subtraction
    commandTable[0][10]  = &sD1;       // Not
    commandTable[0][11]  = &sC1;       // LeftParenthesis
    commandTable[0][12]  = &b1;        // RightParenthesis
    commandTable[0][13]  = &b1;        // End

    // A1
    commandTable[1][0]   = &fatal;     // Expression
    commandTable[1][1]   = &fatal;     // Term
    commandTable[1][2]   = &fatal;     // Factor
    commandTable[1][3]   = &b2;        // Number
    commandTable[1][4]   = &b2;        // Name
    commandTable[1][5]   = &b2;        // Call
    commandTable[1][6]   = &fatal;     // Multiplication
    commandTable[1][7]   = &fatal;     // Division
    commandTable[1][8]   = &sA2;       // Addition
    commandTable[1][9]   = &sA2;       // Subtraction
    commandTable[1][10]  = &fatal;     // Not
    commandTable[1][11]  = &b2;        // LeftParenthesis
    commandTable[1][12]  = &b2;        // RightParenthesis
    commandTable[1][13]  = &r1;        // End

    // A2
    commandTable[2][0]   = &fatal;     // Expression
    commandTable[2][1]   = &sA3;       // Term
    commandTable[2][2]   = &sE1;       // Factor
    commandTable[2][3]   = &sF1;       // Number
    commandTable[2][4]   = &sF1;       // Name
    commandTable[2][5]   = &sG1;       // Call
    commandTable[2][6]   = &b1;        // Multiplication
    commandTable[2][7]   = &b1;        // Division
    commandTable[2][8]   = &b1;        // Addition
    commandTable[2][9]   = &fatal;     // Subtraction
    commandTable[2][10]  = &sD1;       // Not
    commandTable[2][11]  = &sC1;       // LeftParenthesis
    commandTable[2][12]  = &b1;        // RightParenthesis
    commandTable[2][13]  = &b1;        // End

    // A3
    commandTable[3][0]   = &fatal;     // Expression
    commandTable[3][1]   = &fatal;     // Term
    commandTable[3][2]   = &fatal;     // Factor
    commandTable[3][3]   = &fatal;     // Number
    commandTable[3][4]   = &fatal;     // Name
    commandTable[3][5]   = &fatal;     // Call
    commandTable[3][6]   = &sB2;       // Multiplication
    commandTable[3][7]   = &sB2;       // Division
    commandTable[3][8]   = &r2;        // Addition
    commandTable[3][9]   = &r2;        // Subtraction
    commandTable[3][10]  = &fatal;     // Not
    commandTable[3][11]  = &fatal;     // LeftParenthesis
    commandTable[3][12]  = &r2;        // RightParenthesis
    commandTable[3][13]  = &r2;        // End

    // B1
    commandTable[4][0]   = &fatal;     // Expression
    commandTable[4][1]   = &fatal;     // Term
    commandTable[4][2]   = &fatal;     // Factor
    commandTable[4][3]   = &r3;        // Number
    commandTable[4][4]   = &r3;        // Name
    commandTable[4][5]   = &r3;        // Call
    commandTable[4][6]   = &sB2;       // Multiplication
    commandTable[4][7]   = &sB2;       // Division
    commandTable[4][8]   = &r3;        // Addition
    commandTable[4][9]   = &r3;        // Subtraction
    commandTable[4][10]  = &fatal;     // Not
    commandTable[4][11]  = &r3;        // LeftParenthesis
    commandTable[4][12]  = &r3;        // RightParenthesis
    commandTable[4][13]  = &r3;        // End

    // B2
    commandTable[5][0]   = &fatal;     // Expression
    commandTable[5][1]   = &fatal;     // Term
    commandTable[5][2]   = &sB3;       // Factor
    commandTable[5][3]   = &sF1;       // Number
    commandTable[5][4]   = &sF1;       // Name
    commandTable[5][5]   = &sG1;       // Call
    commandTable[5][6]   = &b1;        // Multiplication
    commandTable[5][7]   = &b1;        // Division
    commandTable[5][8]   = &b1;        // Addition
    commandTable[5][9]   = &fatal;     // Subtraction
    commandTable[5][10]  = &sD1;       // Not
    commandTable[5][11]  = &sC1;       // LeftParenthesis
    commandTable[5][12]  = &b1;        // RightParenthesis
    commandTable[5][13]  = &b1;        // End

    // B3
    commandTable[6][0]   = &fatal;     // Expression
    commandTable[6][1]   = &fatal;     // Term
    commandTable[6][2]   = &fatal;     // Factor
    commandTable[6][3]   = &fatal;     // Number
    commandTable[6][4]   = &fatal;     // Name
    commandTable[6][5]   = &fatal;     // Call
    commandTable[6][6]   = &r4;        // Multiplication
    commandTable[6][7]   = &r4;        // Division
    commandTable[6][8]   = &r4;        // Addition
    commandTable[6][9]   = &r4;        // Subtraction
    commandTable[6][10]  = &fatal;     // Not
    commandTable[6][11]  = &fatal;     // LeftParenthesis
    commandTable[6][12]  = &r4;        // RightParenthesis
    commandTable[6][13]  = &r4;        // End

    // C1
    commandTable[7][0]   = &sC2;       // Expression
    commandTable[7][1]   = &sB1;       // Term
    commandTable[7][2]   = &sE1;       // Factor
    commandTable[7][3]   = &sF1;       // Number
    commandTable[7][4]   = &sF1;       // Name
    commandTable[7][5]   = &sG1;       // Call
    commandTable[7][6]   = &b1;        // Multiplication
    commandTable[7][7]   = &b1;        // Division
    commandTable[7][8]   = &b1;        // Addition
    commandTable[7][9]   = &b1;        // Subtraction
    commandTable[7][10]  = &sD1;       // Not
    commandTable[7][11]  = &sC1;       // LeftParenthesis
    commandTable[7][12]  = &b1;        // RightParenthesis
    commandTable[7][13]  = &b1;        // End

    // C2
    commandTable[8][0]   = &fatal;     // Expression
    commandTable[8][1]   = &fatal;     // Term
    commandTable[8][2]   = &fatal;     // Factor
    commandTable[8][3]   = &b3;        // Number
    commandTable[8][4]   = &b3;        // Name
    commandTable[8][5]   = &b3;        // Call
    commandTable[8][6]   = &fatal;     // Multiplication
    commandTable[8][7]   = &fatal;     // Division
    commandTable[8][8]   = &sA2;       // Addition
    commandTable[8][9]   = &sA2;       // Subtraction
    commandTable[8][10]  = &fatal;     // Not
    commandTable[8][11]  = &b3;        // LeftParenthesis
    commandTable[8][12]  = &sC3;       // RightParenthesis
    commandTable[8][13]  = &b3;        // End

    // C3
    commandTable[9][0]   = &fatal;     // Expression
    commandTable[9][1]   = &fatal;     // Term
    commandTable[9][2]   = &fatal;     // Factor
    commandTable[9][3]   = &fatal;     // Number
    commandTable[9][4]   = &fatal;     // Name
    commandTable[9][5]   = &fatal;     // Call
    commandTable[9][6]   = &r8;        // Multiplication
    commandTable[9][7]   = &r8;        // Division
    commandTable[9][8]   = &r8;        // Addition
    commandTable[9][9]   = &r8;        // Subtraction
    commandTable[9][10]  = &fatal;     // Not
    commandTable[9][11]  = &fatal;     // LeftParenthesis
    commandTable[9][12]  = &r8;        // RightParenthesis
    commandTable[9][13]  = &r8;        // End

    // D1
    commandTable[10][0]  = &fatal;     // Expression
    commandTable[10][1]  = &fatal;     // Term
    commandTable[10][2]  = &sD2;       // Factor
    commandTable[10][3]  = &sF1;       // Number
    commandTable[10][4]  = &sF1;       // Name
    commandTable[10][5]  = &sG1;       // Call
    commandTable[10][6]  = &b1;        // Multiplication
    commandTable[10][7]  = &b1;        // Division
    commandTable[10][8]  = &b1;        // Addition
    commandTable[10][9]  = &b1;        // Subtraction
    commandTable[10][10] = &sD1;       // Not
    commandTable[10][11] = &sC1;       // LeftParenthesis
    commandTable[10][12] = &b1;        // RightParenthesis
    commandTable[10][13] = &b1;        // End

    // D2
    commandTable[11][0]  = &fatal;     // Expression
    commandTable[11][1]  = &fatal;     // Term
    commandTable[11][2]  = &fatal;     // Factor
    commandTable[11][3]  = &fatal;     // Number
    commandTable[11][4]  = &fatal;     // Name
    commandTable[11][5]  = &fatal;     // Call
    commandTable[11][6]  = &r6;        // Multiplication
    commandTable[11][7]  = &r6;        // Division
    commandTable[11][8]  = &r6;        // Addition
    commandTable[11][9]  = &r6;        // Subtraction
    commandTable[11][10] = &fatal;     // Not
    commandTable[11][11] = &fatal;     // LeftParenthesis
    commandTable[11][12] = &r6;        // RightParenthesis
    commandTable[11][13] = &r6;        // End

    // E1
    commandTable[12][0]  = &fatal;     // Expression
    commandTable[12][1]  = &fatal;     // Term
    commandTable[12][2]  = &fatal;     // Factor
    commandTable[12][3]  = &r5;        // Number
    commandTable[12][4]  = &r5;        // Name
    commandTable[12][5]  = &r5;        // Call
    commandTable[12][6]  = &r5;        // Multiplication
    commandTable[12][7]  = &r5;        // Division
    commandTable[12][8]  = &r5;        // Addition
    commandTable[12][9]  = &r5;        // Subtraction
    commandTable[12][10] = &fatal;     // Not
    commandTable[12][11] = &r5;        // LeftParenthesis
    commandTable[12][12] = &r5;        // RightParenthesis
    commandTable[12][13] = &r5;        // End

    // F1
    commandTable[13][0]  = &fatal;     // Expression
    commandTable[13][1]  = &fatal;     // Term
    commandTable[13][2]  = &fatal;     // Factor
    commandTable[13][3]  = &r7;        // Number
    commandTable[13][4]  = &r7;        // Name
    commandTable[13][5]  = &r7;        // Call
    commandTable[13][6]  = &r7;        // Multiplication
    commandTable[13][7]  = &r7;        // Division
    commandTable[13][8]  = &r7;        // Addition
    commandTable[13][9]  = &r7;        // Subtraction
    commandTable[13][10] = &fatal;     // Not
    commandTable[13][11] = &r7;        // LeftParenthesis
    commandTable[13][12] = &r7;        // RightParenthesis
    commandTable[13][13] = &r7;        // End

    // G1
    commandTable[14][0]  = &fatal;     // Expression
    commandTable[14][1]  = &fatal;     // Term
    commandTable[14][2]  = &fatal;     // Factor
    commandTable[14][3]  = &b4;        // Number
    commandTable[14][4]  = &b4;        // Name
    commandTable[14][5]  = &b4;        // Call
    commandTable[14][6]  = &b4;        // Multiplication
    commandTable[14][7]  = &b4;        // Division
    commandTable[14][8]  = &b4;        // Addition
    commandTable[14][9]  = &b4;        // Subtraction
    commandTable[14][10] = &fatal;     // Not
    commandTable[14][11] = &sG2;       // LeftParenthesis
    commandTable[14][12] = &b4;        // RightParenthesis
    commandTable[14][13] = &b4;        // End

    // G2
    commandTable[15][0]  = &sG3;       // Expression
    commandTable[15][1]  = &sB1;       // Term
    commandTable[15][2]  = &sE1;       // Factor
    commandTable[15][3]  = &sF1;       // Number
    commandTable[15][4]  = &fatal;     // Name
    commandTable[15][5]  = &sG1;       // Call
    commandTable[15][6]  = &b1;        // Multiplication
    commandTable[15][7]  = &b1;        // Division
    commandTable[15][8]  = &b1;        // Addition
    commandTable[15][9]  = &b1;        // Subtraction
    commandTable[15][10] = &sD1;       // Not
    commandTable[15][11] = &sC1;       // LeftParenthesis
    commandTable[15][12] = &b1;        // RightParenthesis
    commandTable[15][13] = &b1;        // End

    // G3
    commandTable[16][0]  = &fatal;     // Expression
    commandTable[16][1]  = &fatal;     // Term
    commandTable[16][2]  = &fatal;     // Factor
    commandTable[16][3]  = &fatal;     // Number
    commandTable[16][4]  = &fatal;     // Name
    commandTable[16][5]  = &fatal;     // Call
    commandTable[16][6]  = &fatal;     // Multiplication
    commandTable[16][7]  = &fatal;     // Division
    commandTable[16][8]  = &sA2;       // Addition
    commandTable[16][9]  = &fatal;     // Subtraction
    commandTable[16][10] = &fatal;     // Not
    commandTable[16][11] = &fatal;     // LeftParenthesis
    commandTable[16][12] = &sG4;       // RightParenthesis
    commandTable[16][13] = &b3;        // End

    // G4
    commandTable[17][0]  = &fatal;     // Expression
    commandTable[17][1]  = &fatal;     // Term
    commandTable[17][2]  = &fatal;     // Factor
    commandTable[17][3]  = &fatal;     // Number
    commandTable[17][4]  = &fatal;     // Name
    commandTable[17][5]  = &fatal;     // Call
    commandTable[17][6]  = &r9;        // Multiplication
    commandTable[17][7]  = &r9;        // Division
    commandTable[17][8]  = &r9;        // Addition
    commandTable[17][9]  = &r9;        // Subtraction
    commandTable[17][10] = &fatal;     // Not
    commandTable[17][11] = &fatal;     // LeftParenthesis
    commandTable[17][12] = &r9;        // RightParenthesis
    commandTable[17][13] = &r9;        // End
}