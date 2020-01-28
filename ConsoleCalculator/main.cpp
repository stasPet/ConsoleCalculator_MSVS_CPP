#include <iostream>
#include <vector>
#include <sstream>

#include "Lexeme/Lexeme.h"

using namespace clc::lxr;

int main()
{
	std::wistringstream sstream {L"1.30432432409583393E+312412 + 213.33423150349032405893281e-213214;"};
	clc::lxr::Lexeme lexeme;
	
	while (sstream >> lexeme)
	{
		std::wcout << lexeme << std::endl;
	}

	return 0;
}