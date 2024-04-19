#include "heap.h"

int main() 
{
    int size;
    std::string initFile, actFile, outputFile;
    char initOption, actionOption;
    PriorityQueue* heapQueue = nullptr;
    std::vector<std::string> inputData;
    std::vector<std::string> actionData;
    priorityData returnedElement, removedElement;

    while (true) 
    {
        std::cout << "Choose heap initalization method: (D)efault or (S)ize: ";
        std::cin >> initOption;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        initOption = toupper(initOption);

        if (initOption == 'D' || initOption == 'S') 
        {
            break;
        }
        else 
        {
            std::cout << "Invalid input. Please enter 'D', 'd', 'S', or 's'." << std::endl;
        }
    }

    switch (initOption)
    {
    case 'D':
    {
        heapQueue = new PriorityQueue();
    }
    break;

    case 'S':
    {
        std::cout << "What size do you want array: ";
        std::cin >> size;
        checkInt(size);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        heapQueue = new PriorityQueue(size);
    }
    break;

    default:
        break;
    }

    std::cout << "What is the name of your input file: ";
    std::getline(std::cin, initFile);
    initFile += ".txt";
    inputData = heapQueue->readandCheckAction(initFile);
    heapQueue->initialHeapFill(inputData);
    heapQueue->heapSort(); 

    while (true)
    {
        std::cout << "Choose action mode: (U)ser, (F)ile, or (B)oth: ";
        std::cin >> actionOption;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        actionOption = toupper(actionOption);

        if (actionOption == 'U' || actionOption == 'F' || actionOption == 'B')
        {
            break;
        }
        else
        {
            std::cout << "Invalid input. Please enter 'U', 'u', 'F','f','B', or 'b' ." << std::endl;
        }
    }

    switch (actionOption)
    {
    case 'U':
    {
        heapQueue->userActions();
    }
    break;

    case 'F':
    {
        std::cout << "Input name of action file: ";
        std::getline(std::cin, actFile);
        actFile += ".txt";
        actionData = heapQueue->readandCheckAction(actFile);
        heapQueue->preformFileActions(actionData);
    }
    break;

    case 'B':
    {
        std::cout << "Input name of action file: ";
        std::getline(std::cin, actFile);
        actFile += ".txt";
        actionData = heapQueue->readandCheckAction(actFile);
        heapQueue->preformFileActions(actionData);
        heapQueue->userActions();
        heapQueue->toString();
    }
    break;

    default:
        break;
    }

    std::cout << "Input name of output file: ";
    std::getline(std::cin, outputFile);
    heapQueue->setOutputFile(outputFile);
    heapQueue->printStats();
    delete heapQueue;

    return 0;
}
