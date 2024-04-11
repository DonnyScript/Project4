#include "heap.h"

int main() 
{
    int size;
    std::string initFile, actFile, outputFile;
    char menuOption;
    ArrayHeap* heap = nullptr;
    std::vector<std::string> inputData;
    std::vector<std::string> actionData;
    priorityData newElement("code", 7);
    while (true) 
    {
        std::cout << "Choose heap initalization method: (D)efault or (S)ize: ";
        std::cin >> menuOption;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        menuOption = toupper(menuOption);

        if (menuOption == 'D' || menuOption == 'S') {
            break;
        }
        else {
            std::cout << "Invalid input. Please enter 'D', 'd', 'S', or 's'." << std::endl;
        }
    }

    switch (menuOption)
    {
    case 'D':
    {
        heap = new ArrayHeap();
    }
    break;

    case 'S':
    {
        std::cout << "What size do you want array: ";
        std::cin >> size;
        checkInt(size);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        heap = new ArrayHeap(size);
    }
    break;

    default:
        break;
    }

    std::cout << "The option you selected is: " << menuOption << std::endl;

    std::cout << "What is the name of your input file: ";
    std::getline(std::cin, initFile);
    initFile += ".txt";
    inputData = heap->readandCheckAction(initFile);
    heap->initialHeapFill(inputData);

    std::cout << std::endl;
    heap->heapSort();
    std::cout << std::endl;
    heap->printHeap();

    std::cout << std::endl;

    heap->removeMinElement();

    std::cout << "Input name of output file: ";
    std::getline(std::cin, outputFile);
    heap->setOutputFile(outputFile);

    std::cout << "Input name of action file: ";
    std::getline(std::cin, actFile);
    actFile += ".txt";

    actionData = heap->readandCheckAction(actFile);

    std::cout << "Vector Data: " << std::endl;
    for (int i = 0; i < actionData.size(); i++) {
        std::cout << "Data at " << i << ":" << actionData.at(i) << std::endl;
    }

    delete heap;

    return 0;
}
