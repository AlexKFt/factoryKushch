#include "Network.hpp"
#include "iostream"



const int MIN_ID_VALUE = 0;
const int MAX_ID_VALUE = 100;

void Network::addLink()
{
    printIDs(stations);

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
        if (id == -1)
            return -1;
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


void Network::showTopologicalSortResult()
{

    createGraph();
    std::stack<int> networkNumeration = graph.topologicalSort();
    int i = 1;

    while(!networkNumeration.empty())
    {
        std::cout << "Number " << i << ": " 
                  << networkNumeration.top()
                  << std::endl;

        networkNumeration.pop();
        i++;
    }
}


void Network::createGraph()
{
    std::unordered_map<int, std::pair<int, int>> edges;
    std::pair<int, int> stationsPair;

    for (auto& [id, link]: Links)
    {
        stationsPair.first = link.startStationId;
        stationsPair.second = link.finishStationId;

        edges.insert({id, stationsPair});
    }
    graph.setNewState(edges);
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





const double INF = 100000000;


void Network::findLeastDistanceBetweenStations()
{   
    auto checkPoints = getStartAndFinishPoint();
    
    if (checkPoints.first == -1)
        return;

    int start = checkPoints.first;
    int finish = checkPoints.second;

    std::unordered_map<int, int> indexesFromZero;
    std::unordered_map<int, int> originalIndexes;
    int currentIndex = 0;

    for (auto& [id, station]: stations)
        if(CSHasLinks(id))
        {
            originalIndexes.insert_or_assign(currentIndex, id);
            indexesFromZero.insert_or_assign(id, currentIndex++);
        }
    std::vector<std::vector<double>> weights = getWeightsByLength(indexesFromZero);
    std::vector<std::pair<int, double>> distances = graph.dijkstra(weights, indexesFromZero[start], indexesFromZero[finish]);

    int parent = distances[indexesFromZero[finish]].first;

    std::stack<int> path;
    path.push(indexesFromZero[finish]);
    while(parent != -1)
    {
        path.push(parent);
        parent = distances[parent].first;
    }
    while(!path.empty())
    {
        std::cout << originalIndexes[path.top()] << " >> ";
        path.pop();
    }
    std::cout << std::endl;
    std::cout << "The least path between station " << start << " and " << finish << ": "
              << distances[indexesFromZero[finish]].second<< std::endl;
}


std::pair<int, int> Network::getStartAndFinishPoint()
{   
    int start;
    int finish;

    std::cout << "Enter start point: " << std::endl;
    start = getAppropriateNumberIn(Interval(MIN_ID_VALUE, MAX_ID_VALUE, true));
    if (!CSHasLinks(start))
    {
        std::cout << "There is no station with such id in network" << std::endl;
        return std::make_pair(-1, -1);
    }

    std::cout << "Enter finish point: " << std::endl;
    finish = getAppropriateNumberIn(Interval(MIN_ID_VALUE, MAX_ID_VALUE, true));

    if (!CSHasLinks(finish))
    {
        std::cout << "There is no station with such id in network" << std::endl;
        return std::make_pair(-1, -1);
    }

    if (start == finish)
    {
        std::cout << "You have entered the same point as start and finish" << std::endl;
        return std::make_pair(-1, -1);
    }
    return std::make_pair(start, finish);
}


std::vector<std::vector<double>> Network::getWeightsByLength(std::unordered_map<int, int>& indexesFromZero)
{
    int n = indexesFromZero.size();
    std::vector<std::vector<double>> weights (n, std::vector<double>(n, INF));

    for(auto& [id, pipe]: pipes)
    {
        if(PipeHasLinks(id) && checkPipeInRepair(pipe, false))
            weights[indexesFromZero[Links[id].startStationId]][indexesFromZero[Links[id].finishStationId]]
             = std::min(weights[indexesFromZero[Links[id].startStationId]][indexesFromZero[Links[id].finishStationId]],
              pipe.getLength());
    }
    return weights;
}


void Network::findMaxFlow()
{
    auto checkPoints = getStartAndFinishPoint();
    
    if (checkPoints.first == -1)
        return;

    int start = checkPoints.first;
    int finish = checkPoints.second;

    std::unordered_map<int, int> indexesFromZero;
    int currentIndex = 0;

    for (auto& [id, station]: stations)
        if(CSHasLinks(id))
            indexesFromZero.insert_or_assign(id, currentIndex++);

    std::vector<std::vector<std::pair<double, double>>> weights = getWeightsByCapacity(indexesFromZero);
    
    std::cout <<"Maximum flow is: " << graph.findMaximumFlow(weights,indexesFromZero[start],indexesFromZero[finish]) << std::endl;

}


std::vector<std::vector<std::pair<double, double>>> Network::getWeightsByCapacity(std::unordered_map<int, int>& indexesFromZero)
{
    int n = indexesFromZero.size();
    std::vector<std::vector<std::pair<double, double>>> weights (n, std::vector<std::pair<double, double>>(n, std::make_pair(0, 0)));

    for(auto& [id, pipe]: pipes)
    {
        if(PipeHasLinks(id) && checkPipeInRepair(pipe, false))
            weights[indexesFromZero[Links[id].startStationId]][indexesFromZero[Links[id].finishStationId]].first += calculatePipeCapacity(pipe);
            
    }
    return weights;
}

double Network::calculatePipeCapacity(const Pipe& pipe)
{
    return stations[Links[pipe.getId()].startStationId].getWorkload() * 1000000 * pipe.getCapacity();
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