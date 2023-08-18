#include "Graph.hpp"

const double INFd = 100000000;


std::stack<int> Graph::topologicalSort()
{
    std::vector<int> graphNumeration;
    std::unordered_set<int> visited;

    std::stack<int> Stack;

    for(auto& [v, neighbours]: adjacentVertixes)
    {
        if(visited.find(v) == visited.end())
            topologicalSortUtil(v, visited, Stack);
    }
    
    return Stack;
}



void Graph::topologicalSortUtil(int v, std::unordered_set<int>& visited, std::stack<int>& Stack)
{
    visited.insert(v);
    for (auto& adj: adjacentVertixes[v])
    {
        if(visited.find(adj) == visited.end())
            topologicalSortUtil(adj, visited, Stack);
    }
    
    Stack.push(v);
}



void Graph::setNewState(std::unordered_map<int, std::pair<int, int>>& edges)
{
    vertexesInEdge = edges;

    adjacentVertixes.clear();
    for (auto& [edge, vertexes]: vertexesInEdge)
    {
        adjacentVertixes[vertexes.first].insert(vertexes.second);
    }
}



int minElementInVector(std::vector<std::pair<int, double>>& vec, std::vector<bool>& visited)
{
    int id = -1;
    double min = INFd;

    for(int i = 0; i < vec.size(); i++)
        if(!visited[i])
            if(vec[i].second < min)
            {
                min = vec[i].second;
                id = i;
            }
        
    return id;
}



 std::vector<std::pair<int, double>> Graph::dijkstra(const std::vector<std::vector<double>>& weightMatrix, int start, int finish)
{
    
    int n = weightMatrix.size();
    std::vector<bool> visited(n, 0);
    std::vector<std::pair<int, double>> distances(n, std::pair<int, double> (-1, INFd));
    distances[start].second = 0;
    int current = start;
    for(int i = 0; i < n; i++)
    {
        visited[current] = true;
        for(int j = 0; j < n; j++)
        {     
            if(!visited[j])
                if (distances[j].second > distances[current].second + weightMatrix[current][j])
                {
                    distances[j].second = distances[current].second + weightMatrix[current][j];
                    distances[j].first = current;
                }
        }
        if(visited[finish])
            return distances;
        
        current = minElementInVector(distances, visited);
        if (current == -1)
            return distances;
    }
    
    return distances;
}   


const int MAX_E = (int) 1e6;
const int MAX_V = (int) 1e3;
const int INF   = (int) 1e9;

int numOfVertex, numOfEdge, sourceVertex, destinationVertex;
int capacity[MAX_E], onEnd[MAX_E], nextEdge[MAX_E], edgeCount;
int firstEdge[MAX_V], visited[MAX_V];

void addEdge(int u, int v, int cap) {
    
    onEnd[edgeCount] = v;                   
    nextEdge[edgeCount] = firstEdge[u];    
    firstEdge[u] = edgeCount;               
    capacity[edgeCount++] = cap;            
    
    onEnd[edgeCount] = u;                   
    nextEdge[edgeCount] = firstEdge[v];     
    firstEdge[v] = edgeCount;               
    capacity[edgeCount++] = 0;              
}

int findFlow(int u, int flow) {
    if (u == destinationVertex) return flow; 
    visited[u] = true;
    for (int edge = firstEdge[u]; edge != -1; edge = nextEdge[edge]) {
        int to = onEnd[edge];
        if (!visited[to] && capacity[edge] > 0) {
            int minResult = findFlow(to, std::min(flow, capacity[edge])); 
            if (minResult > 0) {                    
                capacity[edge]-= minResult;   
                capacity[edge ^ 1]+= minResult;   
                return minResult;
            }
        }
    }
    return 0; 
}

int Graph::findMaximumFlow(std::vector<std::vector<std::pair<double, double>>>& weights, int start, int finish) 
{
    int n = weights.size();
    std::fill(firstEdge, firstEdge + MAX_V, -1);  

    sourceVertex = start;
    destinationVertex = finish;

    for(int i =0; i < n; i++)
        for(int j =0; j < n; j++)
            if(weights[i][j].first != 0)
                addEdge(i, j, weights[i][j].first);
    
    
    int maxFlow = 0;
    int iterationResult = 0;
    while ((iterationResult = findFlow(sourceVertex, INF)) > 0) {
        std::fill(visited, visited + MAX_V, false);
        maxFlow += iterationResult;
    }
    
    return maxFlow;
}