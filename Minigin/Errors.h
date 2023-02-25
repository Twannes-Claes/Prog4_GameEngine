#pragma once
#include <iostream>

class Expired_Weak_Ptr
{
	public:

	explicit Expired_Weak_Ptr(const std::string& file, const int line, const std::string& extraInfo)
	{

		std::cout << "\033[1;31m"; // set color to red
		std::cout << "Weak_Ptr expired in file: " << file << " line: " << line << '\n';
		std::cout << extraInfo << '\n';
		std::cout << "\033[0m"; // reset color to default

	}
};

