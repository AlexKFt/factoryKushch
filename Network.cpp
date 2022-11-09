#include "Network.hpp"
#include "iostream"


const int MIN_ID_VALUE = 0;
const int MAX_ID_VALUE = 100;

void Network::addLink()
{
    Link link;
    link.stationsIDs = chooseStations();
    link.pipeID = choosePipe();
}


std::unordered_set<int> Network::chooseStations()
{
    std::unordered_set<int> IDs {0};
    return IDs;
}

int Network::choosePipe()
{
    int index;

    std::cout << "Enter diameter of new pipe betwean stations: ";
    std::cout << standartDiametrValues;

    index = getAppropriateNumberIn(Interval(0, (int)standartDiametrValues.size()-1, true));

    std::unordered_set<int> IDs = findPipeByFilter(pipes, checkPipeDiameter, standartDiametrValues[index]);
    
    for (int id: IDs)
        std::cout << id << ' ';
    std::cout << std::endl;

    return 0;
}


void Network::addPipe(Pipe&& pipe)
{
    pipes.insert_or_assign(pipe.getId(), pipe);
}


void Network::addCompressorStation(CompressorStation&& station)
{
    stations.insert_or_assign(station.getId(), station);
}
    

void Network::showObjectsList()
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

void Network::showOperationsWithStations()
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


void Network::showOperationsWithPipes()
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





void Network::saveConfiguration() const
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


void Network::uploadChanges()
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
            addCompressorStation(CompressorStation(fin));
            fin >> std::ws;
        }   
        
        for(int i = 0; i < numberOfPipes; i++)
        {
            addPipe(Pipe(fin));
            fin >> std::ws;
        }
        fin.close();
    }
    else
    {
        std::cout << "This file is not available\n";
    }
}



std::ostream& operator<<(std::ostream& out, const std::vector<double> values)
{
    for(int i = 0; i < values.size(); i++)
        out << i << " - " << values[i] << std::endl;
    return out;
}



void Network::editAllElements(std::unordered_map<int, Pipe>& pipes,
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


void Network::printIDs(const std::unordered_set<int>& indexes)
{
    std::cout << "Your IDs: ";
    for (int id: indexes)
    {
        std::cout << id << "  ";
    }
    std::cout << std::endl;
}


void Network::editAllElements(std::unordered_map<int, CompressorStation>& stations,
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