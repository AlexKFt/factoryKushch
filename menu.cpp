#include "menu.hpp"
#include "CompressorStation.hpp"
#include "Pipe.hpp"
#include <iostream>
#include "utilites.hpp"

void startMenu()
{   
    int commandIndex;
    
    showActions();
    commandIndex = inputForMenu();
    
    pickCommand(commandIndex);
    
}


void showActions()
{
    std::cout << "1: Add pipe" << std::endl;
    std::cout << "2: Add compressor station" << std::endl;
    std::cout << "3: Show object's list" << std::endl;
    std::cout << "4: Edit pipe" << std::endl;
    std::cout << "5: Edit compressor station" << std::endl;
    std::cout << "6: Save" << std::endl;
    std::cout << "7: Upload" << std::endl;
    std::cout << "0: Exit" << std::endl;
}



int inputForMenu()
{
    const int commandIndexLowBound = 0;
    const int commandIndexUpperBound = 7;
    int input;

    for(;;)
    {
        if ((std::cin >> input).good() && (input >= commandIndexLowBound) && (input <= commandIndexUpperBound))   // !!! FIXME magic numbers
        {
            clearInputBuffer();
            return input;
        }
        else if (std::cin.fail())
        {
            clearInputBuffer();
            std::cout << "Error. There should be a number!\n";
        }else
        {
            std::cout << "There is no such instruction\n";
        }
    }
}

void pickCommand(int commandIndex)
{
    if (commandIndex == 1)
    {
        addPipe();
    }
    else if (commandIndex == 2)
    {
        addCompressorStation();
    }
    else if (commandIndex == 3)
    {
        showObjectsList();
    }
    else if (commandIndex == 4)
    {
        editPipe();
    }
    else if (commandIndex == 5)
    {
        editCompressorStation();
    }
    else if (commandIndex == 6)
    {
        saveConfiguration();
    }
    else if (commandIndex == 7)
    {
        uploadChanges();
    }
    else if (commandIndex == 0)
    {
        exit(0);
    }
}

void addPipe()
{
    Pipe pipe;
    createPipe(pipe);
    print(pipe);
    writeInFile(pipe);
}

void addCompressorStation()
{
    CompressorStation cs;
    createCompressorStation(cs);
    print(cs);
    writeInFile(cs);
    CompressorStation cs2;
    readFromFileIn(cs2);
    print(cs);
}

void showObjectsList()
{

}

void editPipe()
{

}

void editCompressorStation()
{

}

void saveConfiguration()
{

}

void uploadChanges()
{
    
}