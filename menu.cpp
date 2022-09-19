#include <iostream>
#include <fstream>
#include "menu.hpp"
#include "utilites.hpp"

int main()
{   
    CompressorStation station1;
    Pipe pipe1;

    int commandIndex;
    
    while(true)
    {
        showActions();
        commandIndex = inputForMenu();
        pickCommand(commandIndex, station1, pipe1);
    }
    
    return 0;
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
        if ((std::cin >> input).good() && (input >= commandIndexLowBound) && (input <= commandIndexUpperBound))  
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

void pickCommand(int commandIndex, CompressorStation& station, Pipe& pipe)
{
    if (commandIndex == 1)
    {
        addPipe(pipe);
    }
    else if (commandIndex == 2)
    {
        addCompressorStation(station);
    }
    else if (commandIndex == 3)
    {
        showObjectsList(station, pipe);
    }
    else if (commandIndex == 4)
    {
        editPipe(pipe);
    }
    else if (commandIndex == 5)
    {
        editCompressorStation(station);
    }
    else if (commandIndex == 6)
    {
        saveConfiguration(station, pipe);
    }
    else if (commandIndex == 7)
    {
        uploadChanges(station, pipe);
    }
    else if (commandIndex == 0)
    {
        exit(0);
    }
}

void addPipe(Pipe& pipe)
{
    InitializePipe(pipe);
}

void addCompressorStation(CompressorStation& station)
{
    InitializeCompressorStation(station);
}

void showObjectsList(CompressorStation& station, Pipe& pipe)
{
    print(pipe);
    print(station);
}

void editPipe(Pipe& pipe)
{
    bool status;

    std::cout << "Enter repair condition of pipe: " << std::endl;
    std::cin >> status;
    clearInputBuffer();
    setRepairConditionTo(pipe, status);
}

void editCompressorStation(CompressorStation& station)
{   
    bool activation;

    std::cout << "To stop one workshop enter 0 " << std::endl;
    std::cout << "To activate new workshop enter 1 " << std::endl;
    std::cin >> activation;
    clearInputBuffer();

    if(activation)
        activateWorkshopAt(station);
    else
        StopWorkshopAt(station);
}

void saveConfiguration(CompressorStation& station, Pipe& pipe)
{
    std::ofstream fout;

    OpenFileForWriting(fout); // !!! FIX ME - BAD NAME FOR FUNCTION
    writeInFile(fout, station);
    writeInFile(fout, pipe);

    fout.close();
}

void uploadChanges(CompressorStation& station, Pipe& pipe)
{
    std::ifstream fin;

    OpenFileForReading(fin);
    readFromFileIn(fin, station);
    readFromFileIn(fin, pipe);
    fin.close();
}