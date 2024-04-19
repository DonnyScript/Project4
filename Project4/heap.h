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
protected:
    priorityData* dataArray;
    int size,initSize;
    std::string inputFile, outputFile;
    std::vector<std::string> userActionValues;
    int ElementsInserted = 0, initHeapDown = 0, userRequestedInserts = 0, userRequestedRemoves = 0, userRequestedTop = 0;
    int userRequestedPrint = 0, totalHeapUp = 0, totalHeapDown = 0;
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

    void toString();

    void setOutputFile(std::string filename);

    std::vector<std::string> readandCheckAction(std::string filename);

    void initialHeapFill(std::vector<std::string> initData); 

    void preformFileActions(std::vector<std::string> actionValues); 

    void heapSort();
    
    void heapify(int index);
   
    void addElement(priorityData element);

    priorityData returnMinElement();

    priorityData removeMinElement();

    bool isEmpty();

    void doubleArraySize();

    void userActions(); 

};
class PriorityQueue : public ArrayHeap
{
public:
    PriorityQueue() : ArrayHeap() {}
    PriorityQueue(int customSize) : ArrayHeap(customSize) {}

    void printStats();
};
#endif 