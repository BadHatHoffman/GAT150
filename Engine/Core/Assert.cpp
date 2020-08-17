#include "pch.h"

void _assert(bool condition, const std::string& conditionString, const std::string& filename, int line, const std::string& funtionName)
{
	if (!condition)
	{
		std::cout << "Assertion Fail: " << conditionString << std::endl;
		std::cout << "Source File: " << filename << std::endl;
		std::cout << "Line: " << line << std::endl;
		std::cout << "Funtion: " << funtionName << std::endl;

		abort();
	}
}

void _assert(bool condition, const std::string& conditionString, const std::string& filename, int line, const std::string& funtionName, const std::string& message)
{
	if (!condition)
	{
		std::cout << "Assertion Fail: " << conditionString << std::endl;
		std::cout << message << std::endl;
		std::cout << "Source File: " << filename << std::endl;
		std::cout << "Line: " << line << std::endl;
		std::cout << "Funtion: " << funtionName << std::endl;

		abort();
	}
}
