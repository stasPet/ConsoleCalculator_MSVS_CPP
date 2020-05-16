#include "LR0Algorithm.h"
#include "BadMassage.h"

using namespace clc::prs;
using namespace lxr;

std::queue<lxr::Token> & LR0Algorithm::GetRPN()
{        
    // 1 - LR0Algorithm: empty input sequence.    
    if (qt.empty() )
        throw BadMassage{1};

    // 2 - LR0Algorithm: the sequence must end with ';'.
    if (qt.back().type != End)
        throw BadMassage{2};

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

void LR0Algorithm::Reduce::Execute()
{
    for (std::size_t i = 0; i < rs; ++i)
    {
        if (host.IsOperation(host.st.top().type) )
                host.rpn.push(host.st.top() );

        host.ss.pop();
        host.st.pop();
    }

    host.tb = rn;
}

void LR0Algorithm::Shift::Execute()
{
    if (host.IsOperand(host.tb.type) )
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
    std::queue<lxr::Token> temp;

    temp.push(host.rpn.back() );    // after token
    temp.push(host.tb);             // come token

    // expected tokens
    while (!expectedTokens.empty() )
    {
        temp.emplace(expectedTokens.front() );
        expectedTokens.pop();
    }

    // 3 - LR0Algorithm: bad sequence detected, after:
    throw BadMassage{3, temp};
}

bool LR0Algorithm::IsOperand(TokenEnum t)
{
    return t == Number || t == Name;
}
bool LR0Algorithm::IsOperation(TokenEnum t)
{
    return t == Multiplication || t == Division ||
        t == Addition ||  t == Subtraction;
}

void LR0Algorithm::PushToken(lxr::Token t)
{
    qt.push(t);
}

LR0Algorithm::LR0Algorithm() :
    commandTable(14, std::vector<Command *>(14) )
{
    // START
    commandTable[0][0]   = &sA1;       // Expression
    commandTable[0][1]   = &sB1;       // Term
    commandTable[0][2]   = &sE1;       // Factor
    commandTable[0][3]   = &sF1;       // Number
    commandTable[0][4]   = nullptr;    // Name
    commandTable[0][5]   = nullptr;    // Call
    commandTable[0][6]   = nullptr;    // Multiplication
    commandTable[0][7]   = nullptr;    // Division
    commandTable[0][8]   = nullptr;    // Addition
    commandTable[0][9]   = nullptr;    // Subtraction
    commandTable[0][10]  = nullptr;    // UnarySubtraction
    commandTable[0][11]  = &sC1;       // LeftParenthesis
    commandTable[0][12]  = nullptr;    // RightParenthesis
    commandTable[0][13]  = nullptr;    // End

    // A1
    commandTable[1][0]   = nullptr;    // Expression
    commandTable[1][1]   = nullptr;    // Term
    commandTable[1][2]   = nullptr;    // Factor
    commandTable[1][3]   = nullptr;    // Number
    commandTable[1][4]   = nullptr;    // Name
    commandTable[1][5]   = nullptr;    // Call
    commandTable[1][6]   = nullptr;    // Multiplication
    commandTable[1][7]   = nullptr;    // Division
    commandTable[1][8]   = &sA2;       // Addition
    commandTable[1][9]   = &sA2;       // Subtraction
    commandTable[1][10]  = nullptr;    // UnarySubtraction
    commandTable[1][11]  = nullptr;    // LeftParenthesis
    commandTable[1][12]  = nullptr;    // RightParenthesis
    commandTable[1][13]  = &r1;        // End

    // A2
    commandTable[2][0]   = nullptr;    // Expression
    commandTable[2][1]   = &sA3;       // Term
    commandTable[2][2]   = &sE1;       // Factor
    commandTable[2][3]   = &sF1;       // Number
    commandTable[2][4]   = nullptr;    // Name
    commandTable[2][5]   = nullptr;    // Call
    commandTable[2][6]   = nullptr;    // Multiplication
    commandTable[2][7]   = nullptr;    // Division
    commandTable[2][8]   = nullptr;    // Addition
    commandTable[2][9]   = nullptr;    // Subtraction
    commandTable[2][10]  = nullptr;    // UnarySubtraction
    commandTable[2][11]  = &sC1;       // LeftParenthesis
    commandTable[2][12]  = nullptr;    // RightParenthesis
    commandTable[2][13]  = nullptr;    // End

    // A3
    commandTable[3][0]   = nullptr;    // Expression
    commandTable[3][1]   = nullptr;     // Term
    commandTable[3][2]   = nullptr;    // Factor
    commandTable[3][3]   = nullptr;    // Number
    commandTable[3][4]   = nullptr;    // Name
    commandTable[3][5]   = nullptr;    // Call
    commandTable[3][6]   = &sB2;       // Multiplication
    commandTable[3][7]   = &sB2;       // Division
    commandTable[3][8]   = &r2;        // Addition
    commandTable[3][9]   = &r2;        // Subtraction
    commandTable[3][10]  = nullptr;    // UnarySubtraction
    commandTable[3][11]  = nullptr;    // LeftParenthesis
    commandTable[3][12]  = &r2;        // RightParenthesis
    commandTable[3][13]  = &r2;        // End

    // B1
    commandTable[4][0]   = nullptr;    // Expression
    commandTable[4][1]   = nullptr;    // Term
    commandTable[4][2]   = nullptr;    // Factor
    commandTable[4][3]   = nullptr;    // Number
    commandTable[4][4]   = nullptr;    // Name
    commandTable[4][5]   = nullptr;    // Call
    commandTable[4][6]   = &sB2;       // Multiplication
    commandTable[4][7]   = &sB2;       // Division
    commandTable[4][8]   = &r3;        // Addition
    commandTable[4][9]   = &r3;        // Subtraction
    commandTable[4][10]  = nullptr;    // UnarySubtraction
    commandTable[4][11]  = nullptr;    // LeftParenthesis
    commandTable[4][12]  = &r3;        // RightParenthesis
    commandTable[4][13]  = &r3;        // End

    // B2
    commandTable[5][0]   = nullptr;    // Expression
    commandTable[5][1]   = nullptr;    // Term
    commandTable[5][2]   = &sB3;       // Factor
    commandTable[5][3]   = &sF1;       // Number
    commandTable[5][4]   = nullptr;    // Name
    commandTable[5][5]   = nullptr;    // Call
    commandTable[5][6]   = nullptr;    // Multiplication
    commandTable[5][7]   = nullptr;    // Division
    commandTable[5][8]   = nullptr;    // Addition
    commandTable[5][9]   = nullptr;    // Subtraction
    commandTable[5][10]  = nullptr;    // UnarySubtraction
    commandTable[5][11]  = &sC1;       // LeftParenthesis
    commandTable[5][12]  = nullptr;    // RightParenthesis
    commandTable[5][13]  = nullptr;    // End

    // B3
    commandTable[6][0]   = nullptr;    // Expression
    commandTable[6][1]   = nullptr;    // Term
    commandTable[6][2]   = nullptr;    // Factor
    commandTable[6][3]   = nullptr;    // Number
    commandTable[6][4]   = nullptr;    // Name
    commandTable[6][5]   = nullptr;    // Call
    commandTable[6][6]   = &r4;        // Multiplication
    commandTable[6][7]   = &r4;        // Division
    commandTable[6][8]   = &r4;        // Addition
    commandTable[6][9]   = &r4;        // Subtraction
    commandTable[6][10]  = nullptr;    // UnarySubtraction
    commandTable[6][11]  = nullptr;    // LeftParenthesis
    commandTable[6][12]  = &r4;        // RightParenthesis
    commandTable[6][13]  = &r4;        // End

    // C1
    commandTable[7][0]   = &sC2;       // Expression
    commandTable[7][1]   = &sB1;       // Term
    commandTable[7][2]   = &sE1;       // Factor
    commandTable[7][3]   = &sF1;       // Number
    commandTable[7][4]   = nullptr;    // Name
    commandTable[7][5]   = nullptr;    // Call
    commandTable[7][6]   = nullptr;    // Multiplication
    commandTable[7][7]   = nullptr;    // Division
    commandTable[7][8]   = nullptr;    // Addition
    commandTable[7][9]   = nullptr;    // Subtraction
    commandTable[7][10]  = nullptr;    // UnarySubtraction
    commandTable[7][11]  = &sC1;       // LeftParenthesis
    commandTable[7][12]  = nullptr;    // RightParenthesis
    commandTable[7][13]  = nullptr;    // End

    // C2
    commandTable[8][0]   = nullptr;    // Expression
    commandTable[8][1]   = nullptr;    // Term
    commandTable[8][2]   = nullptr;    // Factor
    commandTable[8][3]   = nullptr;    // Number
    commandTable[8][4]   = nullptr;    // Name
    commandTable[8][5]   = nullptr;    // Call
    commandTable[8][6]   = nullptr;    // Multiplication
    commandTable[8][7]   = nullptr;    // Division
    commandTable[8][8]   = &sA2;       // Addition
    commandTable[8][9]   = &sA2;       // Subtraction
    commandTable[8][10]  = nullptr;    // UnarySubtraction
    commandTable[8][11]  = nullptr;    // LeftParenthesis
    commandTable[8][12]  = &sC3;       // RightParenthesis
    commandTable[8][13]  = &bh1;       // End

    // C3
    commandTable[9][0]   = nullptr;    // Expression
    commandTable[9][1]   = nullptr;    // Term
    commandTable[9][2]   = nullptr;    // Factor
    commandTable[9][3]   = nullptr;    // Number
    commandTable[9][4]   = nullptr;    // Name
    commandTable[9][5]   = nullptr;    // Call
    commandTable[9][6]   = &r8;        // Multiplication
    commandTable[9][7]   = &r8;        // Division
    commandTable[9][8]   = &r8;        // Addition
    commandTable[9][9]   = &r8;        // Subtraction
    commandTable[9][10]  = nullptr;    // UnarySubtraction
    commandTable[9][11]  = nullptr;    // LeftParenthesis
    commandTable[9][12]  = &r8;        // RightParenthesis
    commandTable[9][13]  = &r8;        // End

    // D1
    commandTable[10][0]  = nullptr;    // Expression
    commandTable[10][1]  = nullptr;    // Term
    commandTable[10][2]  = nullptr;    // Factor
    commandTable[10][3]  = nullptr;    // Number
    commandTable[10][4]  = nullptr;    // Name
    commandTable[10][5]  = nullptr;    // Call
    commandTable[10][6]  = nullptr;    // Multiplication
    commandTable[10][7]  = nullptr;    // Division
    commandTable[10][8]  = nullptr;    // Addition
    commandTable[10][9]  = nullptr;    // Subtraction
    commandTable[10][10] = nullptr;    // UnarySubtraction
    commandTable[10][11] = nullptr;    // LeftParenthesis
    commandTable[10][12] = nullptr;    // RightParenthesis
    commandTable[10][13] = nullptr;    // End

    // D2
    commandTable[11][0]  = nullptr;    // Expression
    commandTable[11][1]  = nullptr;    // Term
    commandTable[11][2]  = nullptr;    // Factor
    commandTable[11][3]  = nullptr;    // Number
    commandTable[11][4]  = nullptr;    // Name
    commandTable[11][5]  = nullptr;    // Call
    commandTable[11][6]  = nullptr;    // Multiplication
    commandTable[11][7]  = nullptr;    // Division
    commandTable[11][8]  = nullptr;    // Addition
    commandTable[11][9]  = nullptr;    // Subtraction
    commandTable[11][10] = nullptr;    // UnarySubtraction
    commandTable[11][11] = nullptr;    // LeftParenthesis
    commandTable[11][12] = nullptr;    // RightParenthesis
    commandTable[11][13] = nullptr;    // End

    // E1
    commandTable[12][0]  = nullptr;    // Expression
    commandTable[12][1]  = nullptr;    // Term
    commandTable[12][2]  = nullptr;    // Factor
    commandTable[12][3]  = nullptr;    // Number
    commandTable[12][4]  = nullptr;    // Name
    commandTable[12][5]  = nullptr;    // Call
    commandTable[12][6]  = &r5;        // Multiplication
    commandTable[12][7]  = &r5;        // Division
    commandTable[12][8]  = &r5;        // Addition
    commandTable[12][9]  = &r5;        // Subtraction
    commandTable[12][10] = nullptr;    // UnarySubtraction
    commandTable[12][11] = nullptr;    // LeftParenthesis
    commandTable[12][12] = &r5;        // RightParenthesis
    commandTable[12][13] = &r5;        // End

    // F1
    commandTable[13][0]  = nullptr;    // Expression
    commandTable[13][1]  = nullptr;    // Term
    commandTable[13][2]  = nullptr;    // Factor
    commandTable[13][3]  = nullptr;    // Number
    commandTable[13][4]  = nullptr;    // Name
    commandTable[13][5]  = nullptr;    // Call
    commandTable[13][6]  = &r6;        // Multiplication
    commandTable[13][7]  = &r6;        // Division
    commandTable[13][8]  = &r6;        // Addition
    commandTable[13][9]  = &r6;        // Subtraction
    commandTable[13][10] = nullptr;    // UnarySubtraction
    commandTable[13][11] = nullptr;    // LeftParenthesis
    commandTable[13][12] = &r6;        // RightParenthesis
    commandTable[13][13] = &r6;        // End
}