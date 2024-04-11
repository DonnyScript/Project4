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

void ArrayHeap::printHeap()
{
    std::cout << "Heap Data: " << std::endl;
    for (int i = 1; i <= ArrayHeap::size; i++) 
    {
        std::cout << "At position " << i << ": " << "[ " << dataArray[i].dataValue << ", " << dataArray[i].priorityValue << " ]" << std::endl;
    }
}

void ArrayHeap::setOutputFile(std::string filename)
{
    filename += ".txt";
    ArrayHeap::outputFile = filename;
}

std::vector<std::string> ArrayHeap::readandCheckAction(std::string filename) 
{
    std::ofstream outputFile(ArrayHeap::outputFile, std::ios::app);
    std::vector<std::string> values;
    std::string data;
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) 
    {
        outputFile << "Unable to open file " + filename << std::endl;
        std::cout << "Unable to open file " + filename << std::endl;
        return values;
    }

    if (inputFile.peek() == std::ifstream::traits_type::eof()) 
    {
        outputFile << "Action file is empty" << std::endl;
        std::cout << "Action file is empty" << std::endl;
        return values;
    }

    while (std::getline(inputFile, data, '"')) 
    {
        std::stringstream ss(data);
        while (std::getline(ss, data, '\n')) 
        {
            if (!data.empty()) 
            {
                values.push_back(data);
            }
        }
        if (std::getline(inputFile, data, '"')) 
        {
            values.push_back(data);
        }
    }
    outputFile.close();
    inputFile.close();

    return values;
}

void ArrayHeap::initialHeapFill(std::vector<std::string> initData)
{
    int priorityData;
    int PrioirtyIndex = 2;
    int ValueIndex = 1;
    for (int i = 1; i <= ArrayHeap::size ; i++)
    {
        if (PrioirtyIndex > initData.size())
        {
            return;
        }
        dataArray[i].dataValue = initData.at(ValueIndex);
        try 
        {
            priorityData = std::stoi(initData.at(PrioirtyIndex));
            dataArray[i].priorityValue = priorityData;
        }
        catch (const std::invalid_argument& ia)
        {
            std::cout << initData.at(PrioirtyIndex) << " - is not a valid input " << std::endl;
        }
        ValueIndex += 3;
        PrioirtyIndex += 3;
    }
}


void ArrayHeap::heapSort() 
{
    ArrayHeap::initSize = 0;
    for (int i = 0; i <= size; ++i)
    {
        if (dataArray[i].priorityValue != NULL)
        {
            initSize++;
        }
    }
    int startIndex = initSize / 2;
    for (int i = startIndex; i >= 0; i--) {
        heapify(i);
    }
}

void ArrayHeap::heapify(int index) 
{
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = 2 * index;
    int smallestIndex = index;


    if (leftChildIndex <= initSize && dataArray[leftChildIndex].priorityValue <= dataArray[smallestIndex].priorityValue) {
        smallestIndex = leftChildIndex;
    }
    if (rightChildIndex <= initSize && dataArray[rightChildIndex].priorityValue <= dataArray[smallestIndex].priorityValue) {
        smallestIndex = rightChildIndex;
    }
    if (dataArray[smallestIndex].priorityValue == NULL )
    {
        return;
    }
    else if (smallestIndex != index) 
    {
        std::swap(dataArray[index], dataArray[smallestIndex]);
        heapify(smallestIndex);
    }
}

void ArrayHeap::addElement(priorityData element)
{
    int startPoint = initSize + 1;
    dataArray[startPoint].priorityValue = element.priorityValue;
    dataArray[startPoint].dataValue = element.dataValue;
    ArrayHeap::heapSort();
}

priorityData ArrayHeap::returnMinElement()
{
    priorityData emptyArray("EmptyArrayOperation", NULL);
    bool isEmpty = false;
    for (int i = 1; i <= ArrayHeap::size; i++)
    {
        if (dataArray[i].priorityValue != NULL && dataArray[i].dataValue.empty()) 
        {
            isEmpty = true;
        }
    }
    if (!isEmpty) 
    {
        std::cout << "Attempt to return element from empty heap" << std::endl;
        return emptyArray;
    }
    return dataArray[1];
}

priorityData ArrayHeap::removeMinElement()
{
    priorityData emptyArray("EmptyArrayOperation", NULL);
    bool isEmpty = false;
    for (int i = 1; i <= ArrayHeap::size; i++)
    {
        if (dataArray[i].priorityValue != NULL && !dataArray[i].dataValue.empty())
        {
            isEmpty = true;
        }
    }
    if (!isEmpty)
    {
        std::cout << "Attempt to return element from empty heap" << std::endl;
        return emptyArray;
    }

    dataArray[1].dataValue = dataArray[initSize].dataValue;
    dataArray[1].priorityValue = dataArray[initSize].priorityValue;
    dataArray[initSize].dataValue = "";
    dataArray[initSize].priorityValue = NULL;
    heapSort();
    printHeap(); 
}
