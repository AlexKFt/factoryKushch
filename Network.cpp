#include "Network.hpp"
#include "iostream"


const int MIN_ID_VALUE = 0;
const int MAX_ID_VALUE = 100;

void Network::addLink()
{
    Link link;
    link.startStationId = chooseStation();
    if(link.startStationId == -1)
        return;

    link.finishStationId = chooseStation();
    if(link.finishStationId == -1)
        return;

    link.pipeID = choosePipe();
    if (link.pipeID != -1)
        Links.insert({link.pipeID, link});
}


int Network::chooseStation()
{
    std::cout << "Enter station id (-1 to exit): " << std::endl; 
    while(1)
    {
        int id = getAppropriateNumberIn(Interval(-1, MAX_ID_VALUE, true));
        if (id==-1)
            return -1;//!!!!!!!!!!!!!!!!!

        if (IsCSAvailable(id))
        {
            return id;
        }
        else
        {
            std::cout << "There is no available station with such id" << std::endl;
        }
    }
}

int Network::choosePipe()
{
    std::cout << "Enter diameter of new pipe between stations: " << std::endl;
    std::cout << standartDiametrValues;

    int index = getAppropriateNumberIn(Interval(0, (int)standartDiametrValues.size()-1, true));

    for (int id: findPipeByFilter(pipes, checkPipeDiameter, standartDiametrValues[index]))
    {
        if (IsPipeAvailable(id))
            return id;
    }

    std::cout << "THere is no free pipe with such diametr. Add new one?\n"
              << "Enter 0 if no, 1 if yes" << std::endl;
    
    if(getAppropriateNumberIn(Interval(0, 1, true)))
        addPipe(Pipe());
    
    if(checkPipeDiameter(pipes[Pipe::maxPipeId-1], standartDiametrValues[index]))
        return Pipe::maxPipeId - 1; 

    return -1;
}


bool Network::IsPipeAvailable(int id)
{
    return Links.count(id) == 0;
}

bool Network::IsCSAvailable(int id)
{
    if(stations.find(id) != stations.end())
        return getCSNumberOfLinks(id) < stations[id].getNumberOfWorkshops();

    return false;
}

void Network::unmountStation(int id)
{
    if (id == -1)
    {
        std::cout << "Enter id of station you want to unmount: " << std::endl;
        id = getAppropriateNumberIn(Interval(MIN_ID_VALUE, MAX_ID_VALUE, true));
    }

    std::unordered_set<int> IDs;
    for (auto& l: Links)
        IDs.insert(l.first);

    for (auto& linkId: IDs)
        if (Links[linkId].containsStation(id))
            deleteLink(linkId);
}

void Network::deleteLink(int id)
{
    showLinks();

    if (id == -1)
    {
        std::cout << "Enter id of pipe you want to unmount: " << std::endl;
        id = getAppropriateNumberIn(Interval(MIN_ID_VALUE, MAX_ID_VALUE, true));
    }

    if (Links.find(id) != Links.end())
    {
        Links.erase(id);
        std::cout << "Link [" << id << "] was deleted" << std::endl;
    }
}



int Network::getCSNumberOfLinks(int id)
{
    int numberOfLinks = 0;
    for (auto& l: Links)
        if (l.second.startStationId == id or l.second.finishStationId == id)
            numberOfLinks++;
    return numberOfLinks;
}




void Network::addPipe(Pipe&& pipe)
{
    pipes.insert_or_assign(pipe.getId(), pipe);
}


void Network::addCompressorStation(CompressorStation&& station)
{
    stations.insert_or_assign(station.getId(), station);
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! repetetive part of code
void Network::deleteAllElements(std::unordered_map<int, Pipe>& container, const std::unordered_set<int>& selection)
{
    for(int id: selection)
    {
        if(PipeHasLinks(id))
        {
            std::cout << "Pipe [" << id << "] is included in network, "
                      << "firstly you need to unmount it" << std::endl;
            continue;
        }
        container.erase(id);
        std::cout << "[" << id << "] was deleted" << std::endl;
    }
}

void Network::deleteAllElements(std::unordered_map<int, CompressorStation>& container, const std::unordered_set<int>& selection)
{
    for(int id: selection)
    {   
        if(CSHasLinks(id))
        {
            std::cout << "Station [" << id << "] is included in network, "
                      << "firstly you need to unmount it" << std::endl;
            continue;
        }
        container.erase(id);
        std::cout << "[" << id << "] was deleted" << std::endl;
    }
}


bool Network::PipeHasLinks(int id)
    {
        return !IsPipeAvailable(id);
    }

bool Network::CSHasLinks(int id)
{
    for (auto& l: Links)
        if (l.second.startStationId == id || l.second.finishStationId)
            return true;
    return false;
}


void Network::showLinks()
{
    for (auto link: Links)
    {
        std::cout<<link.second;
    }
}
    

void Network::showObjectsList()
{
    int commandIndex;
    std::cout << "Enter:\n"
              << "0 - pipes\n"
              << "1 - stations\n"
              << "2 - links\n";

    commandIndex = getAppropriateNumberIn(Interval(0, 2, true));

    if(commandIndex == 0)
        showPipesList();
    else if(commandIndex == 1)
        showStationsList();
    else if(commandIndex == 2)
        showLinks();
}

void Network::showPipesList()
{
    for (const auto& [id, pipe]: pipes)
        std::cout << pipe << std::endl;
}

void Network::showStationsList()
{
    for (const auto& [id, station]: stations)
        std::cout << station << std::endl;
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
        printIDs(indexes);
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
             << pipes.size() << '\n'
             << Links.size() << '\n';

        for(auto& [id, station]: stations)
            fout << station;

        for(auto& [id, pipe]: pipes)
            fout << pipe;

        for (auto& link: Links)
            fout << link.second;

        fout.close();
    }
    else
    {
        std::cout << "File was not created\n";
    } 
}


void Network::loadConfiguration()
{
    std::ifstream fin;
    int numberOfStations, 
        numberOfPipes,
        numberOfLinks;

    if(fileIsReadyForReading(fin)) 
    {
        fin >> numberOfStations;
        fin >> numberOfPipes;
        fin >> numberOfLinks;
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

        for(int i = 0; i < numberOfLinks; i++)
        {
            Link link;
            fin >> link;
            Links.insert({link.pipeID, link});
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