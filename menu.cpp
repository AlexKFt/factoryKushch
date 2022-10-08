#include <iostream>
#include <fstream>
#include "menu.hpp"
#include "const.hpp"



int main()
{   
    std::unordered_map<int, CompressorStation> stations;
    std::unordered_map<int, Pipe> pipes;

    int commandIndex;
    
    while(true)
    {
        showActions();
        commandIndex = inputForMenu();
        pickCommand(commandIndex, stations, pipes);
    }
}


void showActions()
{
    std::cout << "Command list: " << std::endl;
    std::cout << "1: Add pipe" << std::endl;
    std::cout << "2: Add compressor station" << std::endl;
    std::cout << "3: Show object's list" << std::endl;
    std::cout << "4: Actions with pipes" << std::endl;
    std::cout << "5: Actioons with compressor stations" << std::endl;
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

    input = getAppropriateNumberIn(Interval(commandIndexLowBound, commandIndexUpperBound, true));
    
    return input;
}


void pickCommand(int commandIndex, 
                 std::unordered_map<int, CompressorStation>& stations, 
                 std::unordered_map<int, Pipe>& pipes)
{
    if (commandIndex == 1)
    {
        addPipeTo(pipes, Pipe());
    }
    else if (commandIndex == 2)
    {
        addCompressorStationTo(stations, CompressorStation());
    }
    else if (commandIndex == 3)
    {
        showObjectsList(stations, pipes);
    }
    else if (commandIndex == 4)
    {
        showOperationsWith(pipes);
    }
    else if (commandIndex == 5)
    {
        showOperationsWith(stations);
    }
    else if (commandIndex == 6)
    {
        saveConfiguration(stations, pipes);
    }
    else if (commandIndex == 7)
    {
        uploadChanges(stations, pipes);
    }
    else if (commandIndex == 0)
    {
        askForStorage(stations, pipes);
        exit(0);
    }
}


void addPipeTo(std::unordered_map<int, Pipe>& pipes, Pipe&& pipe)
{
    int static pipeCounter = 1;

    pipes.insert_or_assign(pipeCounter , pipe);
    pipeCounter++;
}


void addCompressorStationTo(std::unordered_map<int, CompressorStation>& stations,
                            CompressorStation&& station)
{
    int static stationCounter = 1;

    stations.insert_or_assign(stationCounter, station);
    stationCounter++;
}


void showObjectsList(std::unordered_map<int, CompressorStation>& stations, 
                     std::unordered_map<int, Pipe>& pipes)
{
    for (const auto& [id, station]: stations)
    {
        std::cout << "id: " << id << '\n' << station << std::endl;
    }
    for (const auto& [id, pipe]: pipes)
    {
        std::cout << "id " << id << '\n' << pipe << std::endl;
    }

}


std::unordered_set<int> selectIDs()
{
    std::unordered_set<int> IDs;
    int element = -1;
    
    std::cout << "Enter indexes of elements, to exit enter 0" << std::endl;
    
    while(element)
    {
        std::cout << ">> ";
        element = getAppropriateNumberIn(Interval(MIN_ID_VALUE, MAX_ID_VALUE, true));
        IDs.insert(element);
    }
    return IDs;
}


void edit(Pipe& pipe, int id)
{
    bool status;

    std::cout << "Enter repair condition for pipe [" << id  << "]" <<std::endl
              << "0 - pipe is working" << std::endl
              << "1 - pipe is under repair" << std::endl << ">> ";

    status = getAppropriateNumberIn(Interval(0, 1, true));
    
    pipe.setRepairCondition(status);
}


void edit(CompressorStation& station, int id)
{   
    bool activation;
    
    std::cout << "Station [" << id << "]: "  << std::endl
              << "To stop one workshop enter 0 " << std::endl
              << "To activate new workshop enter 1 " << std::endl;

    std::cin >> activation;
    clearInputBuffer();

    if(activation)
        station.activateWorkshop();
    else
        station.stopWorkshop();
}


void saveConfiguration(std::unordered_map<int, CompressorStation>& stations, 
                       std::unordered_map<int, Pipe>& pipes)
{
    std::ofstream fout;

    if ((stations.size() + pipes.size() > 0) && fileIsReadyForWriting(fout))
    {
        fout << stations.size() << '\n' 
             << pipes.size() << '\n';

        for(auto& [id, station]: stations)
            fout << station;

        for(auto& [id, pipe]: pipes)
            fout << pipe;

        fout.close();
    }
    else
    {
        std::cout << "File was not created\n";
    } 
}


void uploadChanges(std::unordered_map<int, CompressorStation>& stations, 
                   std::unordered_map<int, Pipe>& pipes)
{
    std::ifstream fin;
    int numberOfStations, 
        numberOfPipes;

    if(fileIsReadyForReading(fin)) 
    {
        fin >> numberOfStations;
        fin >> numberOfPipes;
        fin >> std::ws;

        for(int i = 0; i < numberOfStations; i++)
        {
            addCompressorStationTo(stations, CompressorStation(fin));
            fin >> std::ws;
        }   
        
        for(int i = 0; i < numberOfPipes; i++)
        {
            addPipeTo(pipes, Pipe(fin));
            fin >> std::ws;
        }
        fin.close();
    }
    else
    {
        std::cout << "This file is not available\n";
    }
}


void askForStorage(std::unordered_map<int, CompressorStation>& stations, 
                   std::unordered_map<int, Pipe>& pipes)
{
    std::cout << "Do you want to save current data?" << std::endl
              << " Enter 0 if no\n Enter 1 if yes" << std::endl;
              
    bool shouldBeSaved;

    std::cin  >> shouldBeSaved;
    clearInputBuffer();

    if (shouldBeSaved)
    {
        saveConfiguration(stations, pipes);
    }   
}