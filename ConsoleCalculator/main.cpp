#include <iostream>
#include <vector>
#include <sstream>

#include "Lexeme/Lexer.h"

using namespace clc::lxr;

int main()
{
	std::wistringstream sstream {L"1.30432432409583393E+312412 + 213.33423150349032405893281e-213214;"};

	clc::lxr::Lexer lexer{sstream};

	clc::lxr::Lexeme lexeme;
	clc::lxr::Lexeme exit;
	
	while (true)
	{
		lexeme = lexer.GetLexeme();
		std::wcout << lexeme << std::endl;

		if (lexeme.type == Type::Empty)
			break;
	}

	return 0;
}