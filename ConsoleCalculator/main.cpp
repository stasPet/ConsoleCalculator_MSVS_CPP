#include <iostream>
#include <sstream>

#include "Calculator.h"

using namespace clc;

int main()
{
	std::wistringstream sstream{L"(1+2) * 3;1+ 2;"};

	clc::Calculator calculator{sstream};

	std::wstring_view result1 = calculator.GetResult();
	std::wstring_view result2 = calculator.GetResult();

	return 0;
}