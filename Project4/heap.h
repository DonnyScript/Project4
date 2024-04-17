#ifndef HEAP_H
#define HEAP_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

struct priorityData
{
    std::string dataValue;
    int priorityValue;

    priorityData() : dataValue(""), priorityValue(NULL) {}

    priorityData(const std::string& data, int priority) : dataValue(data), priorityValue(priority) {}
};

void checkInt(int& param);

class ArrayHeap 
{
private:
    priorityData* dataArray;
    int size,initSize;
    std::string inputFile,outputFile;
public:
    ArrayHeap() : size(10), initSize(0)
    {
        dataArray = new priorityData[size + 1];
    }

    ArrayHeap(int customSize) : size(customSize), initSize(0)
    {
        dataArray = new priorityData[size + 1];
    }

    ~ArrayHeap() 
    {
        delete[] dataArray;
    }

    void printHeap();

    void setOutputFile(std::string filename);

    std::vector<std::string> readandCheckAction(std::string filename);

    void initialHeapFill(std::vector<std::string> initData);

    void heapSort();
    
    void heapify(int index);
   
    void addElement(priorityData element);

    priorityData returnMinElement();

    priorityData removeMinElement();

    bool isEmpty();

    void doubleArraySize();

    std::string toString();

    void userFillArray(); 

};

#endif 