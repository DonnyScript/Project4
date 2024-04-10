#include "heap.h"

void checkInt(int& input)// To use set call with what you want to check at the parameter
{
	while (std::cin.fail())
	{
		std::cout << "Put valid number: ";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cin >> input;
	}
}

void ArrayHeap::printSize()
{
	std::cout << ArrayHeap::size << std::endl;
}
