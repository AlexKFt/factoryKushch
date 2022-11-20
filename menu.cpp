#include "menu.hpp"





int main()
{   
    Network net;

    int commandIndex;
    
    while(true)
    {
        showActions();
        commandIndex = inputForMenu();
        pickCommand(commandIndex, net);
    }
}


void showActions()
{
    std::cout << "Command list: " << std::endl;
    std::cout << "1: Add pipe" << std::endl;
    std::cout << "2: Add compressor station" << std::endl;
    std::cout << "3: Show object's list" << std::endl;
    std::cout << "4: Find pipes by filter" << std::endl;
    std::cout << "5: Find compressor stations by filter" << std::endl;
    std::cout << "6: Save" << std::endl;
    std::cout << "7: Upload" << std::endl;
    std::cout << "8: Add connection between stations"  << std::endl;
    std::cout << "9: Delete connection between stations" << std::endl;
    std::cout << "10: Unmount station from network" << std::endl;
    std::cout << "0: Exit" << std::endl;
    std::cout << "\nEnter command index(0 - 7) : " << std::endl;
}


int inputForMenu()
{
    const int commandIndexLowBound = 0;
    const int commandIndexUpperBound = 10;
    int input;

    input = getAppropriateNumberIn(Interval(commandIndexLowBound, commandIndexUpperBound, true));
    
    return input;
}


void pickCommand(int commandIndex, Network& net)
{
    if (commandIndex == 1)
    {
        net.addPipe(Pipe());
    }
    else if (commandIndex == 2)
    {
        net.addCompressorStation(CompressorStation());
    }
    else if (commandIndex == 3)
    {
        net.showObjectsList();
    }
    else if (commandIndex == 4)
    {
        net.showOperationsWithPipes();
    }
    else if (commandIndex == 5)
    {
        net.showOperationsWithStations();
    }
    else if (commandIndex == 6)
    {

        net.saveConfiguration();
    }
    else if (commandIndex == 7)
    {
        net.loadConfiguration();
    }
    else if (commandIndex == 8)
    {
        net.addLink();
    }
    else if(commandIndex == 9)
    {
        net.deleteLink();
    }
    else if (commandIndex == 10)
    {
        net.unmountStation();
    }
    else if (commandIndex == 0)
    {
        askForStorage(net);
        exit(0);
    }
}



void askForStorage(Network& net)
{
    std::cout << "Do you want to save current data?" << std::endl
              << " Enter 0 if no\n Enter 1 if yes" << std::endl;
              
    bool shouldBeSaved;

    std::cin  >> shouldBeSaved;
    clearInputBuffer();

    if (shouldBeSaved)
    {
        net.saveConfiguration();
    }   
}