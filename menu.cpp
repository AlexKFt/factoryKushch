#include <iostream>
#include <fstream>
#include "menu.hpp"
#include "utils.hpp"

int main()
{   
    CompressorStation station;
    Pipe pipe;

    int commandIndex;

    
    while(true)
    {
        showActions();
        commandIndex = inputForMenu();
        pickCommand(commandIndex, station, pipe);
    }
    
    return 0;
}


void showActions()
{
    std::cout << "Command list: " << std::endl;
    std::cout << "1: Add pipe" << std::endl;
    std::cout << "2: Add compressor station" << std::endl;
    std::cout << "3: Show object's list" << std::endl;
    std::cout << "4: Edit pipe" << std::endl;
    std::cout << "5: Edit compressor station" << std::endl;
    std::cout << "6: Save" << std::endl;
    std::cout << "7: Upload" << std::endl;
    std::cout << "0: Exit" << std::endl;
    std::cout << "\nEnter command index(0 - 7) : ";
}


int inputForMenu()
{
    const int commandIndexLowBound = 0;
    const int commandIndexUpperBound = 7;
    int input;

    input = getAppropriateNumberInLimits(Interval(commandIndexLowBound, commandIndexUpperBound, true));
    
    return input;
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
        askForStorage(station, pipe);
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

void showObjectsList(const CompressorStation& station, const Pipe& pipe)
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

void saveConfiguration(const CompressorStation& station,const Pipe& pipe)
{
    std::ofstream fout;
    int numberOfStations = 0, 
        numberOfPipes = 0;

    if(!station.wasDefined)
    {
        std::cout << "There is no station\n";
    }
    else
    {
        numberOfStations = 1;
    }
    if (!pipe.wasDefined)
    {
        std::cout << "There is no pipe\n";
    }
    else
    {
        numberOfPipes = 1;
    }
    if ((numberOfStations + numberOfPipes > 0) && fileIsReadyForWriting(fout))
    {
        fout << numberOfStations << '\n' 
             << numberOfPipes << '\n';

        for(int i = 0; i < numberOfStations; ++i)
            writeInFile(fout, station);

        for(int i = 0; i < numberOfPipes; ++i)
            writeInFile(fout, pipe);

        fout.close();
    }
    else
    {
        std::cout << "File was not created\n";
    }
    
}

void uploadChanges(CompressorStation& station, Pipe& pipe)
{
    std::ifstream fin;
    int numberOfStations, 
        numberOfPipes;

    if(fileIsReadyForReading(fin)) 
    {
        fin >> numberOfStations;
        fin >> numberOfPipes;
        fin.ignore(1024, '\n');
        
        for(int i = 0; i < numberOfStations; i++)
        {
            readFromFileIn(fin, station);
        }   
        
        for(int i = 0; i < numberOfPipes; i++)
        {
            readFromFileIn(fin, pipe);
        }
        fin.close();
    }
    else
    {
        std::cout << "This file is not available\n";
    }
}

void askForStorage(const CompressorStation& station,const Pipe& pipe)
{
    std::cout << "Do you want to save current data?" << std::endl
              << " Enter 0 if no\n Enter 1 if yes" << std::endl;
              
    bool shouldBeSaved;

    std::cin  >> shouldBeSaved;
    clearInputBuffer();

    if (shouldBeSaved)
    {
        saveConfiguration(station, pipe);
    }   
}