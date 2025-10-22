
#pragma once
#include <vector>
#include <string>

class Graph {
    int n;
    std::vector<std::vector<int>> adj;
public:
    Graph(int n);
    void addEdge(int u, int v);
    std::vector<int> BFS(int start) const;
};
