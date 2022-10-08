#ifndef MENU_H
#define MENU_H

#include "CompressorStation.hpp"
#include "Pipe.hpp"
#include <unordered_map>
#include <unordered_set>
#include "utils.hpp"


void showActions();


int inputForMenu();


void pickCommand(int commandIndex, 
                 std::unordered_map<int, CompressorStation>& stations, 
                 std::unordered_map<int, Pipe>& pipes);


void addPipeTo(std::unordered_map<int, Pipe>& pipes, Pipe&& pipe);


void addCompressorStationTo(std::unordered_map<int, CompressorStation>& stations,
                            CompressorStation&& station);


void showObjectsList(std::unordered_map<int, CompressorStation>& stations, 
                     std::unordered_map<int, Pipe>& pipes);


template<typename T>
void showOperationsWith(std::unordered_map<int, T>& container)
{
    int commandIndex;

    std::cout << "Enter 0 to delete some elements" << std::endl
              << "Enter 1 to edit some elelments" << std::endl;

    commandIndex = getAppropriateNumberIn(Interval(0, 1, true));

    if (commandIndex == 0)
    {
        deleteElementsIn(container);
    }
    else if (commandIndex == 1)
    {
        editElementsIn(container);
    } 
}


std::unordered_set<int> selectIDs();

template<typename T>
void deleteElementsIn(std::unordered_map<int, T>& container)
{
    std::unordered_set<int> IDs = selectIDs();

    for (int id: IDs)
    {
        if(container.find(id) != container.end())
            container.erase(id);
    }  
}


template<typename T>
void editElementsIn(std::unordered_map<int, T>& container)
{
    std::unordered_set<int> IDs = selectIDs();

    for (int id: IDs)
    {
        if(container.find(id) != container.end())
            edit(container[id], id);
    }
}


void edit(Pipe& pipe, int id);


void edit(CompressorStation& station, int id);


void saveConfiguration(std::unordered_map<int, CompressorStation>& stations, 
                       std::unordered_map<int, Pipe>& pipes);


void uploadChanges(std::unordered_map<int, CompressorStation>& stations, 
                   std::unordered_map<int, Pipe>& pipes);


void askForStorage(std::unordered_map<int, CompressorStation>& stations, 
                   std::unordered_map<int, Pipe>& pipes);







#endif