#pragma once
#include <iostream>

class Expired_Weak_Ptr
{
	public:
	explicit Expired_Weak_Ptr(const std::string& file, const int line)
	{
		std::cout << "Weak_Ptr expired in file: " << file << " line: " << line << ';' << '\n';
	}
};

