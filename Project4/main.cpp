#include <iostream>
#include <memory>
#include <string>
#include "Check.h"

struct priorityData 
{
    std::string dataValue;
    int priorityValue;

    priorityData() : priorityValue(0) {}

    priorityData(const std::string& data, int priority) : dataValue(data), priorityValue(priority) {}

    ~priorityData() {
        std::cout << "priorityData object with dataValue: " << dataValue << " and priorityValue: " << priorityValue << " is destroyed." << std::endl;
    }
};

int main() 
{
    int size;
    std::cout << "Choose array size: ";
    std::cin >> size;

    priorityData* arrayHeap = new priorityData[size];

    for (int i = 0; i < size; i++) 
    {
        std::string data;
        int priority;
        std::cout << "Enter value of array element " << i << ": ";
        std::cin >> priority;
        checkInt(priority);
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter data for element: ";
        std::getline(std::cin, data);
        arrayHeap[i].dataValue = data;
        arrayHeap[i].priorityValue = priority;
    }
  

    std::cout << "Array index and values" << std::endl;

    for (int i = 0; i < size; i++) 
    {
        std::cout << arrayHeap[i].dataValue << std::endl;
    }

    return 0;
}
