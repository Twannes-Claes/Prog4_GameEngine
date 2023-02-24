#pragma once
#include <iostream>

class Expired_Weak_Ptr
{
	public:
	explicit Expired_Weak_Ptr(const std::string& info)
	{
		std::cout << "Weak_Ptr expired in file: " << __FILE__ << " line: " << __LINE__ << ';' << '\n';
		std::cout << info;
	}
};

