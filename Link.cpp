#include <iostream>
#include <fstream>
#include "Link.hpp"


bool Link::containsStation(int id)
{
    return (startStationId == id) || (finishStationId == id);
}


std::ifstream& operator>>(std::ifstream& in, Link& link)
{
    in >> link.startStationId;
    in >> link.pipeID;
    in >> link.finishStationId;

    return in;
}

std::ostream& operator<<(std::ostream& out, const Link& link)
{
    out << link.startStationId << " --" << link.pipeID << "--> " <<link.finishStationId << std::endl;
    return out;
}

std::ofstream& operator<<(std::ofstream& out, const Link& link)
{
    out << link.startStationId << '\n'
         << link.pipeID << '\n'
         << link.finishStationId << '\n';
    return out;
}