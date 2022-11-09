#include "Network.hpp"
#include "iostream"


std::ostream& operator<<(std::ostream& out, const std::vector<double> values)
{
    for(int i = 0; i < values.size(); i++)
        out << i << " - " << values[i] << std::endl;
    return out;
}


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


