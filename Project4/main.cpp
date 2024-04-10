#include "heap.h"

int main() 
{
    int size;
    std::string initFile, actFile, outputFile;
    char menuOption;

    while (true) {
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
        ArrayHeap heap;
    }
    break;

    case 'S':
    {
        std::cout << "What size do you want array: ";
        std::cin >> size;
        checkInt(size);
        ArrayHeap heap(size);
    }
    break;

    default:
        break;
    }

    std::cout << "The option you selected is: " << menuOption << std::endl;

    return 0;
}
