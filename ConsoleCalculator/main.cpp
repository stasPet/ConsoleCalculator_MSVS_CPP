#include <iostream>
#include <vector>
#include <sstream>

#include "Calculator.h"

using namespace clc;

#include "Lexer/Token.h"

int main()
{
	std::wistringstream sstream {L"tg;"};
	Calculator calculator{sstream};

	return 0;
}