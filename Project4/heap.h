#ifndef HEAP_H
#define HEAP_H
#include <iostream>
#include <string>

struct priorityData
{
    std::string dataValue;
    int priorityValue;

    priorityData() : dataValue("default"), priorityValue(0) {}

    priorityData(const std::string& data, int priority) : dataValue(data), priorityValue(priority) {}

    ~priorityData() {
        std::cout << "priorityData object with dataValue: " << dataValue << " and priorityValue: " << priorityValue << " is destroyed." << std::endl;
    }
};


void checkInt(int& param);

class ArrayHeap 
{
private:
    priorityData* dataArray;
    int size;
public:
    ArrayHeap() : size(10) {
        dataArray = new priorityData[size];
    }

    ArrayHeap(int customSize) : size(customSize) {
        dataArray = new priorityData[size];
    }

    ~ArrayHeap() {
        delete[] dataArray;
    }
    void printSize();
};


#endif 
