#ifndef MENU_H
#define MENU_H

#include "Network.hpp"
#include "utils.hpp"


extern const int MIN_ID_VALUE;
extern const int MAX_ID_VALUE;


void showActions();


int inputForMenu();


void pickCommand(int commandIndex, 
                 std::unordered_map<int, CompressorStation>& stations, 
                 std::unordered_map<int, Pipe>& pipes);


void addPipeTo(std::unordered_map<int, Pipe>& pipes, Pipe&& pipe);


void addCompressorStationTo(std::unordered_map<int, CompressorStation>& stations,
                            CompressorStation&& station);


void showObjectsList(const std::unordered_map<int, CompressorStation>& stations, 
                     const std::unordered_map<int, Pipe>& pipes);


void showOperaitonsWithStations(std::unordered_map<int, CompressorStation>& stations);


void showOperationsWithPipes(std::unordered_map<int, Pipe>& pipes);


void printIDs(const std::unordered_set<int>& indexes);


template<typename T>
std::unordered_set<int> selectIDs(T& container)
{
    std::unordered_set<int> IDs;
    int element = -1;
    std::cout << "Enter indexes of elements, to exit enter 0" << std::endl;
    
    while(true)
    {
        element = getAppropriateNumberIn(Interval(MIN_ID_VALUE, MAX_ID_VALUE, true));
        
        if(!element)
            break;

        if(container.find(element) != container.end())
            IDs.insert(element);
        else
            std::cout << "There is no element with such id" << std::endl;
        
    }
    printIDs(IDs);

    return IDs;
}

template<typename T>
void deleteAllElements(std::unordered_map<int, T>& container, const std::unordered_set<int>& selection)
{
    for(int id: selection)
    {
        container.erase(id);
        std::cout << "[" << id << "] was deleted" << std::endl;
    }
}


template<typename T>
void deleteElementsIn(std::unordered_map<int, T>& container, std::unordered_set<int> selection)
{
    int commandIndex;

    if(selection.size() == 1)
    {
        deleteAllElements(container, selection);
        return;
    }

    std::cout << "Enter 0 to delete all selected elements" << std::endl
              << "Enter 1 to delete some of these elements" << std::endl;

    commandIndex = getAppropriateNumberIn(Interval(0, 1, true));

    printIDs(selection);

    if (!commandIndex)
    {
        deleteAllElements(container, selection);
    }
    if (commandIndex)
    {
        printIDs(selection);
        std::unordered_set<int> indexIntersection = selectIDs(selection);
        deleteAllElements(container ,indexIntersection);
    }    

}


template<typename T>
void chooseElemensForEditing(std::unordered_map<int, T>& container, std::unordered_set<int> selection)
{
    int commandIndex;

    

    if(selection.size() == 1)
    { 
        editAllElements(container, selection);
        return;
    }

    std::cout << "Enter 0 to edit all selected elements" << std::endl
              << "Enter 1 to edit some of these elements" << std::endl;

    commandIndex = getAppropriateNumberIn(Interval(0, 1, true));

    printIDs(selection); 

    if (!commandIndex)
    {
        editAllElements(container, selection);
    }
    else
    {
        std::unordered_set<int> indexIntersection = selectIDs(selection);
        editAllElements(container, indexIntersection);
    }
}   


template<typename T>
void chooseEditOrDelete(std::unordered_map<int, T>& container, std::unordered_set<int> indexes)
{

    std::cout << "Enter 0 to start deleting " << std::endl
              << "Enter 1 to start editing" << std::endl;

    int commandIndex;

    commandIndex = getAppropriateNumberIn(Interval(0, 1, true));
    
    if (commandIndex == 0)
    {
        deleteElementsIn(container, indexes);
    }
    else if (commandIndex == 1)
    {
        chooseElemensForEditing(container, indexes);
    }
}


void editAllElements(std::unordered_map<int, CompressorStation>& stations,
                     std::unordered_set<int>& selection);


void editAllElements(std::unordered_map<int, Pipe>& pipes,
                     std::unordered_set<int>& selection);


void saveConfiguration(const std::unordered_map<int, CompressorStation>& stations, 
                       const std::unordered_map<int, Pipe>& pipes);


void uploadChanges(std::unordered_map<int, CompressorStation>& stations, 
                   std::unordered_map<int, Pipe>& pipes);


void askForStorage(const std::unordered_map<int, CompressorStation>& stations, 
                   const std::unordered_map<int, Pipe>& pipes);



#endif