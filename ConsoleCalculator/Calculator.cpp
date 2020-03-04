#include "Calculator.h"

#include <istream>
#include <queue>

using namespace clc::lxr;
using namespace clc::prs;
using namespace clc;

TokenType Calculator::GetTokenType(LexemeType t)
{
    switch (t)
    {
        case LexemeType::Operand:          return TokenType::Operand;
        case LexemeType::Operation:        return TokenType::Operation;
        case LexemeType::Function:         return TokenType::Function;
        case LexemeType::LeftParenthesis:  return TokenType::LeftParenthesis;
        case LexemeType::RightParenthesis: return TokenType::RightParenthesis;
        case LexemeType::Bad:              return TokenType::Bad;
    }

    return TokenType::Empty;
}

WString Calculator::Calculate(std::wistream & stream)
{
    prs::TableOfSymbolsT & tableOfSymbols =
        parser.GetTableOfSymbols();

    std::queue<Token> tokenBuffer;
    Lexeme lexeme;

    while (stream)
    {
        lexeme = lexer.GetLexeme(stream);
        tokenBuffer.push
        (
            Token
            {
                GetTokenType(lexeme.typeValue),
                tableOfSymbols.SetSymbol(lexeme.stringValue)
            }
        );
    }

    AST ast{parser.GetAST(tokenBuffer) };
    ast.Show(ast.GetRoot(), tableOfSymbols);
    // ...

    return L"";
}