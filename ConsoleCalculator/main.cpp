#include <iostream>
#include <sstream>

#include "Calculator.h"

using namespace clc;

int main()
{
	std::wistringstream sstream{L"567+sqrt( 5.);-(7/fde-5.e+5);"};

	clc::Calculator calculator{sstream};
	std::wstring_view result = calculator.GetResult();

	return 0;
}