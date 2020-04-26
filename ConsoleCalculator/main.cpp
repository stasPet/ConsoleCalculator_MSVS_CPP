#define DEBUG

#include <iostream>
#include <sstream>

#include "Calculator.h"

using namespace clc;

int main()
{
	std::wistringstream sstream{L"1+2;3*4;5e-1+3.   ;"};
	clc::Calculator calculator{sstream};

	std::wstring result1 = calculator.GetResult();
	std::wstring result2 = calculator.GetResult();
	std::wstring result3 = calculator.GetResult();

	return 0;
}