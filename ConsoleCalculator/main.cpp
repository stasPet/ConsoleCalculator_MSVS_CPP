#include <iostream>
#include <vector>
#include <sstream>

#include "Lexer/Lexer.h"
#include "TableOfSymbols.h"

using namespace clc::lxr;
using namespace clc;

int main()
{
	std::wistringstream sstream {L"1.30432432409583393E+312412 + 213.33423150349032405893281e-213214 \
		1.30432432409583393E+312412 + 213.33423150349032405893281e-213214 + sqrt(78.);"};

	TableOfSymbols tableOfSymbol;
	Lexer lexer{sstream, tableOfSymbol};
	Token token;
	
	while (true)
	{
		token = lexer.GetToken();

		if (token.tokenType == TokenType::Empty)
			break;
	}

	return 0;
}