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
    std::unordered_map<int, std::pair<int, int>> vertexesInEdge;
 

    void topologicalSortUtil(int v, std::unordered_set<int>& visited, std::stack<int>& Stack);

public:
    void setNewState(std::unordered_map<int, std::pair<int, int>>&);

    std::stack<int> topologicalSort();

    std::vector<std::pair<int, double>> dijkstra(const std::vector<std::vector<double>>& weightMatrix, int start, int finish);

    int findMaximumFlow(std::vector<std::vector<std::pair<double, double>>>& weights, int start, int finish);

};



#endif