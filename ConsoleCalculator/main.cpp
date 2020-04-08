#include <iostream>
#include <sstream>

#include "Calculator.h"

using namespace clc;

int main()
{
	std::wistringstream sstream{L"1 + 2 + 3;"};

	clc::Calculator calculator{sstream};
	std::wstring_view result = calculator.GetResult();

	return 0;
}