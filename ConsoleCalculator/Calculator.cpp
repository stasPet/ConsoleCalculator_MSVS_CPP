#include <istream>
#include "Calculator.h"

using namespace clc::lxr;
using namespace clc::prs;
using namespace clc;

TokenType Calculator::GetTokenType(Lexeme const & lexeme)
{
    switch (lexeme.typeValue)
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
    Lexeme lexeme;

    while (stream)
    {
        lexeme = lexer.GetLexeme(stream);

        parser.AddToken
        (
            {
                GetTokenType(lexeme),
                tableOfSymbol.SetSymbol(lexeme.stringValue)
            }
        );
    }

    ast = parser.GetAST();

    return L"";
}