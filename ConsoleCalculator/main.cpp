#include <iostream>
#include <sstream>

#include "Calculator.h"

using namespace clc;

int main()
{
	std::wistringstream sstream {L";"};

	Calculator calculator;
	clc::lxr::WString result = calculator.Calculate(sstream);

	return 0;
}