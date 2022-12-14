#ifndef GRAPH_H
#define GRAPH_H


#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include "CompressorStation.hpp"


class Graph
{
private:

    std::unordered_map<int, std::unordered_set<int>> adjacentVertixes;
    std::unordered_map<int, std::vector<int>> vertexesInEdge;

    void topologicalSortUtil(int v, std::unordered_set<int>& visited, std::stack<int>& Stack);

public:
    void setNewState(std::unordered_map<int, std::vector<int>>);

    std::stack<int> topologicalSort();
};



#endif