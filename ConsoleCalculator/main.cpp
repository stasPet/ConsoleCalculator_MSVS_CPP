#include <iostream>
#include <vector>
#include <sstream>

#include "Lexer/Lexer.h"
#include "TableOfSymbols.h"

using namespace clc::lxr;

int main()
{
	clc::TableOfSymbols table{L"100", L"200", L"300", L"200"};
	clc::TableOfSymbols t = table;

	clc::ExpressionStringType e = table.GetSymbol(1);

	std::wistringstream sstream {L"1.30432432409583393E+312412 + 213.33423150349032405893281e-213214;"};
	clc::lxr::Lexer lexer{sstream};
	clc::lxr::Lexeme lexeme;
	
	while (true)
	{
		lexeme = lexer.GetLexeme();
		std::wcout << lexeme << std::endl;

		if (lexeme.type == Type::Empty)
			break;
	}

	return 0;
}