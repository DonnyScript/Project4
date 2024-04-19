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


void ArrayHeap::toString()
{
    std::cout << "Heap Data: " << std::endl;
    for (int i = 1; i <= ArrayHeap::size; i++) 
    {
        std::cout << "At position " << i << ": " << "( " << dataArray[i].dataValue << ", " << dataArray[i].priorityValue << " )" << std::endl;
    }
}

void ArrayHeap::setOutputFile(std::string filename)
{
    filename += ".txt";
    ArrayHeap::outputFile = filename;
}

void ArrayHeap::setActionFile(std::string filename)
{
    ArrayHeap::actionFile = filename;
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
    for (int i = 1; i <= initData.size(); i++) 
    {
        if (ArrayHeap::initSize == ArrayHeap::size)
        {
            
            ArrayHeap::doubleArraySize();
        }

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
        ArrayHeap::ElementsInserted++;
        ArrayHeap::initSize++; 
    }
}


std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void ArrayHeap::preformFileActions(std::vector<std::string> actionValues)
{
    if (ArrayHeap::initSize == ArrayHeap::size)
    {
        std::cout << "Array is full doubling the size" << std::endl;
        ArrayHeap::doubleArraySize();
    }

    std::transform(actionValues.begin(), actionValues.end(), actionValues.begin(), trim);
    int insertHeapCtr = ArrayHeap::initSize + 1;
    
    for (int i = 0; i < actionValues.size(); i++)
    {
        if (actionValues[i] == "I")
        {
            int tempString;

            dataArray[insertHeapCtr].dataValue = actionValues[i + 1];
            tempString = stoi(actionValues[i + 2]);
            dataArray[insertHeapCtr].priorityValue = tempString;
            ArrayHeap::heapSort();
            insertHeapCtr++;
        }
        else if (actionValues[i] == "R")
        {
            dataArray[1].dataValue = "";
            dataArray[1].priorityValue = NULL;
        }
        else if (actionValues[i] == "S")
        {
            std::cout << "Top element is: " << "(" << "\"" << dataArray[1].dataValue << "\"" << "," << dataArray[1].priorityValue << ")" << std::endl;
        }
        else if (actionValues[i] == "A")
        {
            ArrayHeap::toString();
        }
    }
    ArrayHeap::initSize = insertHeapCtr - 1;
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
        ArrayHeap::totalHeapDown++;
        heapify(smallestIndex);
    }
}

void ArrayHeap::addElement(priorityData element)
{
    if (ArrayHeap::initSize == ArrayHeap::size) 
    {
       ArrayHeap::doubleArraySize();
    }
    int startPoint = initSize + 1;
    dataArray[startPoint].priorityValue = element.priorityValue;
    dataArray[startPoint].dataValue = element.dataValue;
    ArrayHeap::heapSort();
}

priorityData ArrayHeap::returnMinElement()
{
    priorityData InvalidArray("InvalidArrayOperation", NULL);
    
    if (!isEmpty()) 
    {
        std::cout << "Attempt to return element from empty heap" << std::endl;
        return InvalidArray;
    }

    return dataArray[1];
}

priorityData ArrayHeap::removeMinElement()
{
    priorityData InvalidArray("InvalidArrayOperation", NULL);
    priorityData removedElement;

    if (!isEmpty())
    {
        std::cout << "Attempt to return element from empty heap" << std::endl;
        return InvalidArray;
    }

    removedElement.dataValue = dataArray[1].dataValue;
    removedElement.priorityValue = dataArray[1].priorityValue;
    dataArray[1].dataValue = dataArray[initSize].dataValue;
    dataArray[1].priorityValue = dataArray[initSize].priorityValue;
    dataArray[initSize].dataValue = "";
    dataArray[initSize].priorityValue = NULL;
    heapSort();
    return removedElement;
}

bool ArrayHeap::isEmpty()
{
    bool isEmpty = false;
    for (int i = 1; i <= ArrayHeap::size; i++)
    {
        if (dataArray[i].priorityValue != NULL && !dataArray[i].dataValue.empty())
        {
            isEmpty = true;
        }
    }
    return isEmpty;
}

void ArrayHeap::doubleArraySize() {
    int newSize = size * 2;

    priorityData* newArray = new priorityData[newSize + 1];

    for (int i = 1; i <= initSize; ++i) {
        newArray[i] = dataArray[i];
    }

    delete[] dataArray;
    ArrayHeap::dataArray = newArray;
    ArrayHeap::size = newSize;
    std::cout << "Array size doubled to: " << ArrayHeap::size << std::endl;
}


void ArrayHeap::userActions()
{
    int startPos = 0; 
    char actionOption;
    std::stringstream ss;

    if (ArrayHeap::initSize == ArrayHeap::size)
    {
        std::cout << "Array is full doubling" << std::endl;
        ArrayHeap::doubleArraySize();
    }

    if (ArrayHeap::initSize != ArrayHeap::size)
    {
        startPos = initSize + 1;
    }
    else
    {
        startPos = ArrayHeap::size;
    }

    std::cout << "Starting user actions, here is the current array:" << std::endl;
    ArrayHeap::toString();
    std::cout << std::endl;
    std::cout << "You have " << ArrayHeap::size - ArrayHeap::initSize << " positions to fill" << std::endl;

    for (int i = startPos; i <= ArrayHeap::size;)
    {
        while (true)
        {
            std::cout << "Choose action method: I(nsesrt), R(emove), S(ee top element), A(ll elements in string), or Q(uit):";
            std::cin >> actionOption;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            actionOption = toupper(actionOption);

            if (actionOption == 'I' || actionOption == 'R' || actionOption == 'S' || actionOption == 'A' || actionOption == 'Q')
            {
                break;
            }
            else
            {
                std::cout << "Invalid input. Please enter 'I', 'R', 'S', or 'A' " << std::endl;
            }
        }

        switch (actionOption)
        {
        case 'I':
        {
            std::string tempString, userString;
            int tempPriority;

            std::cout << "Enter string data: ";
            std::getline(std::cin, tempString);

            std::cout << "Enter priority: ";
            std::cin >> tempPriority;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            checkInt(tempPriority);

            dataArray[i].dataValue = tempString;
            dataArray[i].priorityValue = tempPriority;
            ArrayHeap::heapSort();


            userActionValues.push_back("I ");
            userActionValues.push_back(tempString + " ");
            userString = std::to_string(tempPriority);
            userActionValues.push_back(userString + "\n");

            std::cout << "String data: " << tempString << ", Priority: " << tempPriority << std::endl << std::endl;
            ss << "String data: " << tempString << ", Priority: " << tempPriority << std::endl << std::endl;
            std::string iOption = ss.str();
            userActionValues.push_back(iOption);

            ss.str("");
            ss.clear();
            userRequestedInserts++;
            i++;
        }
        break;

        case 'R':
        {
            userActionValues.push_back("R");
            dataArray[1].dataValue = "";
            dataArray[1].priorityValue = NULL;
            userRequestedRemoves++;
        }
        break;

        case 'S':
        {
            userActionValues.push_back("S ");
            std::cout << "Top element is: " << "(" << "\"" << dataArray[1].dataValue << "\"" << "," << dataArray[1].priorityValue << ")" << std::endl;
            ss << "Top element is: " << "(" << "\"" << dataArray[1].dataValue << "\"" << "," << dataArray[1].priorityValue << ")" << std::endl;
            std::string sOption = ss.str();
            userActionValues.push_back(sOption);

            ss.str("");
            ss.clear();
            userRequestedTop++;
        }
        break;

        case 'A':
        {
            userActionValues.push_back("A");
            userRequestedPrint++;
            ArrayHeap::toString();
        }
        break;

        case 'Q':
        {
            return;
        }

        default:
            break;
        }    
    }
}

void PriorityQueue::printStats()
{
    std::ofstream outputFile(PriorityQueue::outputFile, std::ios::app);
    std::ifstream file(PriorityQueue::actionFile);
    int totalUserHeapActions = userRequestedInserts + userRequestedRemoves + userRequestedTop + userRequestedPrint;

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::cout << std::endl;
    std::cout << "Heap created with size: " << PriorityQueue::size << std::endl;
    std::cout << "Priority Queue Initialization" << std::endl;
    std::cout << " Elements inserted: " << PriorityQueue::ElementsInserted << std::endl;
    std::cout << " Number of heap-down actions to create heap order: " << PriorityQueue::initHeapDown << std::endl << std::endl;

    if (PriorityQueue::size <= 20)
    {
        PriorityQueue::toString();
        std::cout << std::endl;
    }

    std::cout << "Priority Queue Initialization complete" << std::endl << std::endl;
    std::cout << "User Action File " << std::endl;
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
   
    std::cout << "User Action File Complete" << std::endl << std::endl;
    std::cout << "User Action Interface" << std::endl << std::endl; 

    for (int i = 0; i < userActionValues.size(); i++)
    {
        std::cout << userActionValues[i];
    }
    std::cout << "User Action Interface Complete" << std::endl << std::endl; 

    std::cout << "Total number of Inserts - Initialization: " << PriorityQueue::ElementsInserted << std::endl;
    std::cout << "Total number of heap-down actions - Initialization: " << PriorityQueue::initHeapDown << std::endl;
    std::cout << "Total number of user requested Inserts: " << PriorityQueue::userRequestedInserts << std::endl;
    std::cout << "Total number of user requested Removes: " << PriorityQueue::userRequestedRemoves << std::endl;
    std::cout << "Total number of user requested Return Top: " << PriorityQueue::userRequestedTop << std::endl;
    std::cout << "Total number of user requested Print: " << PriorityQueue::userRequestedPrint << std::endl;
    std::cout << "Total number of heap actions for user actions: " << totalUserHeapActions << std::endl;
    std::cout << "     Total number of heap-up actions:          " << PriorityQueue::totalHeapUp << std::endl;
    std::cout << "     Total number of heap-down actions:        " << PriorityQueue::totalHeapDown << std::endl;

    //_______________________________________________________________________________________________________________//
    
    outputFile << "Heap created with size: " << PriorityQueue::size << std::endl;
    outputFile << "Priority Queue Initialization" << std::endl;
    outputFile << " Elements inserted: " << PriorityQueue::ElementsInserted << std::endl;
    outputFile << " Number of heap-down actions to create heap order: " << PriorityQueue::initHeapDown << std::endl << std::endl;

    if (PriorityQueue::size <= 20)
    {
        PriorityQueue::toString();
        outputFile << std::endl;
    }

    outputFile << "Priority Queue Initialization complete" << std::endl << std::endl;
    outputFile << "User Action File " << std::endl;
    std::string Outputline;
    while (std::getline(file, Outputline)) {
        outputFile << line << std::endl;
    }

    outputFile << "User Action File Complete" << std::endl << std::endl;
    outputFile << "User Action Interface" << std::endl << std::endl;

    for (int i = 0; i < userActionValues.size(); i++)
    {
        outputFile << userActionValues[i];
    }
    outputFile << "User Action Interface Complete" << std::endl << std::endl;

    outputFile << "Total number of Inserts - Initialization: " << PriorityQueue::ElementsInserted << std::endl;
    outputFile << "Total number of heap-down actions - Initialization: " << PriorityQueue::initHeapDown << std::endl;
    outputFile << "Total number of user requested Inserts: " << PriorityQueue::userRequestedInserts << std::endl;
    outputFile << "Total number of user requested Removes: " << PriorityQueue::userRequestedRemoves << std::endl;
    outputFile << "Total number of user requested Return Top: " << PriorityQueue::userRequestedTop << std::endl;
    outputFile << "Total number of user requested Print: " << PriorityQueue::userRequestedPrint << std::endl;
    outputFile << "Total number of heap actions for user actions: " << totalUserHeapActions << std::endl;
    outputFile << "     Total number of heap-up actions:          " << PriorityQueue::totalHeapUp << std::endl;
    outputFile << "     Total number of heap-down actions:        " << PriorityQueue::totalHeapDown << std::endl;

    file.close();
    outputFile.close();
}