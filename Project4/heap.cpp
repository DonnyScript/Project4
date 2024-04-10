#include "heap.h"

void checkInt(int& input)
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

void ArrayHeap::setInitFile(std::string filename)
{
    filename += ".txt";
	ArrayHeap::inputFile = filename;
}

void ArrayHeap::setOutputFile(std::string filename)
{
    filename += ".txt";
    ArrayHeap::outputFile = filename;
}


std::vector<std::string> ArrayHeap::readandCheckAction(std::string filename) {
    std::ofstream outputFile(ArrayHeap::outputFile, std::ios::app);
    std::vector<std::string> values;
    std::string data;
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        outputFile << "Unable to open file " + filename << std::endl;
        std::cout << "Unable to open file " + filename << std::endl;
        return values;
    }

    if (inputFile.peek() == std::ifstream::traits_type::eof()) {
        outputFile << "Action file is empty" << std::endl;
        std::cout << "Action file is empty" << std::endl;
        return values;
    }

    while (inputFile >> data) {
        values.push_back(data);
    }

    outputFile.close();
    inputFile.close();

    return values;
}
