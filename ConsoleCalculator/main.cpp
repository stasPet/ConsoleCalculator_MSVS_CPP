#include <iostream>
#include <sstream>

#include "Calculator.h"
#include "Exception.h"

using namespace clc;

int main()
{
	std::wistringstream sstream{L"3-1/(2;"};
	Calculator calculator{sstream};

	while (calculator)
	{
		try
		{
			std::wcout << calculator.GetResult()
				<< std::endl;
		}
		catch (Exception & e)
		{
			std::wcerr << e.GetMessage();

			if (e.IsFatalError() )
				break;
		}
	}

	return 0;
}