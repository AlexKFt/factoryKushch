#ifndef GRAPH_H
#define GRAPH_H


#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "CompressorStation.hpp"


class Graph
{
private:
    std::vector<CompressorStation> networkNumeration;
    std::unordered_map<int, std::unordered_set<int>> setsOfNeighbours;
    std::unordered_map<int, std::vector<int>> setsOfStationsPairs;
};



#endif