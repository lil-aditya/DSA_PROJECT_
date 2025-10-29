#pragma once
#include <bits/stdc++.h>
using namespace std;

class Graph {
private:
    map<int,vector<int>> adjList;
    int numNodes;
public:
    Graph(int nodes);
    void addEdge(int u, int v);
    void BFS(int startNode);

    vector<int> findShortestPath(int startNode, int endNode);
};
