#include <iostream>
#include "tuple.h"
#include <string>
#include <iostream>

int main()
{
	tuple t3{ 1, 2.0, std::string("hello"),std::string("world") };
	std::cout << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t) << ", " << get<3>(t2) << "\n";

	tuple t2{ 1, 2.0, std::string(“hello”), std::string(“world”) };
	std::cout << std::boolalpha << "tuples are equal : " << (t2 == t3) << "\n";

	return 0;
}
