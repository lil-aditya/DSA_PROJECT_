
#include "graph_routing.hpp"
#include <queue>

Graph::Graph(int n): n(n), adj(n) {}

void Graph::addEdge(int u, int v) {
    if (u<0 || u>=n || v<0 || v>=n) return;
    adj[u].push_back(v);
    adj[v].push_back(u);
}

std::vector<int> Graph::BFS(int start) const {
    std::vector<int> order;
    if (start < 0 || start >= n) return order;
    std::vector<char> vis(n, 0);
    std::queue<int> q;
    q.push(start);
    vis[start]=1;
    while(!q.empty()) {
        int u=q.front(); q.pop();
        order.push_back(u);
        for (int v: adj[u]) if(!vis[v]) { vis[v]=1; q.push(v); }
    }
    return order;
}
