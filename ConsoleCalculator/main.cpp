#include <iostream>
#include <sstream>

#include "Calculator.h"

using namespace clc;

int main()
{
	std::wistringstream sstream{L"1;2;"};

	clc::Calculator calculator;
	clc::lxr::WString result = calculator.Calculate(sstream);

	return 0;
}