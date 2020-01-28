#include <iostream>
#include <vector>
#include <sstream>

#include "Lexeme/Lexeme.h"

using namespace clc::lxr;

int main()
{
	std::wistringstream sstream {L"1.*5-(1+2.3e-1);/a-c+56;"};;
	clc::lxr::Lexeme lexeme;
	
	while (std::wcin >> lexeme)
	{
		std::wcout << lexeme << std::endl;
	}

	return 0;
}