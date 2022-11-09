#include "menu.hpp"


const int MIN_ID_VALUE = 0;
const int MAX_ID_VALUE = 100;


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
    std::cout << "4: Find pipes by filter" << std::endl;
    std::cout << "5: Find compressor stations by filter" << std::endl;
    std::cout << "6: Save" << std::endl;
    std::cout << "7: Upload" << std::endl;
    std::cout << "8: Add connection between stations"  << std::endl;
    std::cout << "0: Exit" << std::endl;
    std::cout << "\nEnter command index(0 - 7) : " << std::endl;
}


int inputForMenu()
{
    const int commandIndexLowBound = 0;
    const int commandIndexUpperBound = 8;
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
        showOperationsWithPipes(pipes);
    }
    else if (commandIndex == 5)
    {
        showOperaitonsWithStations(stations);
    }
    else if (commandIndex == 6)
    {
        saveConfiguration(stations, pipes);
    }
    else if (commandIndex == 7)
    {
        uploadChanges(stations, pipes);
    }
    else if (commandIndex == 8)
    {
        
    }
    else if (commandIndex == 0)
    {
        askForStorage(stations, pipes);
        exit(0);
    }
}


void addPipeTo(std::unordered_map<int, Pipe>& pipes, Pipe&& pipe)
{
    pipes.insert_or_assign(pipe.getId(), pipe);
}


void addCompressorStationTo(std::unordered_map<int, CompressorStation>& stations,
                            CompressorStation&& station)
{
    stations.insert_or_assign(station.getId(), station);
}


void showObjectsList(const std::unordered_map<int, CompressorStation>& stations, 
                     const std::unordered_map<int, Pipe>& pipes)
{
    for (const auto& [id, station]: stations)
    {
        std::cout << station << std::endl;
    }
    for (const auto& [id, pipe]: pipes)
    {
        std::cout << pipe << std::endl;
    }

}

void showOperaitonsWithStations(std::unordered_map<int, CompressorStation>& stations)
{
    int commandIndex;
    std::unordered_set<int> indexes;

    std::cout << "Enter 0 to find station by name" << std::endl
              << "Enter 1 to find station by percent of active workshops" << std::endl;

    commandIndex = getAppropriateNumberIn(Interval(0, 2, true));

    if (commandIndex == 0)
    {
        std::string partOfName;
        std::cout << "Enter station name: ";

        getline(std::cin, partOfName);
        indexes = findCompressorStationByFilter(stations, checkName, partOfName);

        printIDs(indexes);
    }
    else if(commandIndex == 1)
    {
        std::cout << "Enter station workload" << std::endl;

        double activeWorkshopPercent = getAppropriateNumberIn(Interval(0, 100, true));
        indexes = findCompressorStationByFilter(stations, checkStationWorkload, activeWorkshopPercent);

        printIDs(indexes);
    }
    if(!indexes.size())
    {
        std::cout << "There is no stations for actions"<< std::endl;
        return;
    }
    
    chooseEditOrDelete(stations, indexes);

}

void showOperationsWithPipes(std::unordered_map<int, Pipe>& pipes)
{
    int commandIndex;
    std::unordered_set<int> indexes;

    std::cout << "Enter 0 to find pipes by name" << std::endl
              << "Enter 1 to find pipes in repair" << std::endl
              << "Enter 2 to find working pipe" << std::endl;

    commandIndex = getAppropriateNumberIn(Interval(0, 2, true));

    if (commandIndex == 0)
    {
        std::string partOfName;
        std::cout << "Enter pipe name: ";

        getline(std::cin, partOfName);
        indexes = findPipeByFilter(pipes, checkName, partOfName);
    }
    else if (commandIndex == 1)
    {
        indexes = findPipeByFilter(pipes, checkPipeInRepair, true);
        printIDs(indexes);
    }
    else if(commandIndex == 2)
    {
        indexes = findPipeByFilter(pipes, checkPipeInRepair, false);
        printIDs(indexes);
    }
    if(!indexes.size())
    {
        std::cout << "There is no pipes for actions"<< std::endl;
        return;
    }

    chooseEditOrDelete(pipes, indexes);
}


void printIDs(const std::unordered_set<int>& indexes)
{
    std::cout << "Your IDs: ";
    for (int id: indexes)
    {
        std::cout << id << "  ";
    }
    std::cout << std::endl;
}


void editAllElements(std::unordered_map<int, Pipe>& pipes,
                     std::unordered_set<int>& selection)
{
    std::cout << "Enter new condition of pipes" << std::endl
              << "0 - pipes are working" << std::endl
              << "1 - pipes are under repair" << std::endl;

    bool status = getAppropriateNumberIn(Interval(0, 1, true));

    for (int id: selection)
    {
        (pipes[id]).edit(status);
        std::cout << "Pipe [" << id << "] repair condition was changed to " << status << std::endl;
    }
}


void editAllElements(std::unordered_map<int, CompressorStation>& stations,
                     std::unordered_set<int>& selection)
{
    std::cout << "Enter workload for stations" << std::endl;
    
    double stationWorkload = getAppropriateNumberIn(Interval(0., 100., true));

    for (int id: selection)
    {
        std::cout << "Station [" << id << "]: "  << std::endl;
        (stations[id]).edit(stationWorkload);
    }
}


void saveConfiguration(const std::unordered_map<int, CompressorStation>& stations, 
                       const std::unordered_map<int, Pipe>& pipes)
{
    std::ofstream fout;

    if (fileIsReadyForWriting(fout))
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


void askForStorage(const std::unordered_map<int, CompressorStation>& stations, 
                   const std::unordered_map<int, Pipe>& pipes)
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