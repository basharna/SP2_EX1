/*
ID: 212487144
Email: nbashar4@gmail.com
*/

#include "Algorithms.hpp"
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>

int Algorithms::isConnected(Graph &g)
{
    std::vector<bool> visited(g.getNumVertices(), false);
    std::queue<int> q;
    q.push(0);
    visited[0] = true;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        for (int i = 0; i < g.getNumVertices(); ++i)
        {
            if (g.getAdjacencyMatrix()[current][i] && !visited[i])
            {
                q.push(i);
                visited[i] = true;
            }
        }
    }

    for (bool v : visited)
    {
        if (!v)
            return 0; // If any vertex is not visited, graph is not connected
    }
    return 1;
}

std::vector<int> Algorithms::shortestPath(Graph &g, int start, int end)
{
    std::vector<int> dist(g.getNumVertices(), std::numeric_limits<int>::max());
    std::vector<int> prev(g.getNumVertices(), -1);
    dist[start] = 0;
    std::queue<int> q;
    q.push(start);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < g.getNumVertices(); ++v)
        {
            if (g.getAdjacencyMatrix()[u][v])
            {
                if (dist[v] > dist[u] + g.getAdjacencyMatrix()[u][v])
                {
                    dist[v] = dist[u] + g.getAdjacencyMatrix()[u][v];
                    prev[v] = u;
                    q.push(v);
                }
            }
        }
    }

    if (dist[end] == std::numeric_limits<int>::max())
    {
        return {-1}; // No path found, return -1
    }

    std::vector<int> path;
    for (int at = end; at != -1; at = prev[at])
    {
        path.insert(path.begin(), at);
    }

    return path;
}

bool isDirectedCycleUtil(Graph& g, int v, std::vector<bool>& visited, std::vector<bool>& recStack) {
    visited[v] = true;
    recStack[v] = true;

    for (int u = 0; u < g.getNumVertices(); ++u) {
        if (g.getAdjacencyMatrix()[v][u]) {
            if (!visited[u]) {
                if (isDirectedCycleUtil(g, u, visited, recStack))
                    return true;
            } else if (recStack[u]) {
                return true; // Cycle detected
            }
        }
    }

    recStack[v] = false; // Backtrack
    return false;
}

bool isDirectedCycle(Graph& g) {
    std::vector<bool> visited(g.getNumVertices(), false);
    std::vector<bool> recStack(g.getNumVertices(), false);

    for (int v = 0; v < g.getNumVertices(); ++v) {
        if (!visited[v]) {
            if (isDirectedCycleUtil(g, v, visited, recStack))
                return true;
        }
    }

    return false; // No cycle found
}

bool isUndirectedCycleUtil(Graph& g, int v, int parent, std::vector<bool>& visited) {
    visited[v] = true;

    for (int u = 0; u < g.getNumVertices(); ++u) {
        if (g.getAdjacencyMatrix()[v][u]) {
            if (!visited[u]) {
                if (isUndirectedCycleUtil(g, u, v, visited))
                    return true;
            } else if (u != parent) {
                return true; // Cycle detected
            }
        }
    }

    return false;
}

bool isUndirectedCycle(Graph& g) {
    std::vector<bool> visited(g.getNumVertices(), false);

    for (int v = 0; v < g.getNumVertices(); ++v) {
        if (!visited[v]) {
            if (isUndirectedCycleUtil(g, v, -1, visited))
                return true;
        }
    }

    return false; // No cycle found
}


bool Algorithms::isContainsCycle(Graph& g) {
    if (g.getIsDirected()) {
        return isDirectedCycle(g);
    } else {
        return isUndirectedCycle(g);
    }
}

bool Algorithms::isBipartite(Graph &g)
{
    std::vector<int> colors(g.getNumVertices(), -1);

    colors[0] = 1;
    std::queue<int> q;
    q.push(0);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        if (g.getAdjacencyMatrix()[u][u])
        {
            return false;
        }

        for (int v = 0; v < g.getNumVertices(); ++v)
        {
            if (g.getAdjacencyMatrix()[u][v] && colors[v] == -1)
            {
                colors[v] = 1 - colors[u];
                q.push(v);
            }
            else if (g.getAdjacencyMatrix()[u][v] && colors[v] == colors[u])
            {
                return false;
            }
        }
    }

    return true;
}

bool Algorithms::negativeCycle(Graph &g)
{
    std::vector<int> dist(g.getNumVertices(), std::numeric_limits<int>::max());

    // Initialize the distance of the source vertex to 0
    dist[0] = 0;

    // Relax edges repeatedly
    for (int i = 0; i < g.getNumVertices() - 1; ++i)
    {
        for (int u = 0; u < g.getNumVertices(); ++u)
        {
            for (int v = 0; v < g.getNumVertices(); ++v)
            {
                if (g.getAdjacencyMatrix()[u][v] != 0 && dist[u] + g.getAdjacencyMatrix()[u][v] < dist[v])
                {
                    dist[v] = dist[u] + g.getAdjacencyMatrix()[u][v];
                }
            }
        }
    }

    // Check for negative cycles
    for (int u = 0; u < g.getNumVertices(); ++u)
    {
        for (int v = 0; v < g.getNumVertices(); ++v)
        {
            if (g.getAdjacencyMatrix()[u][v] != 0 && dist[u] + g.getAdjacencyMatrix()[u][v] < dist[v])
            {
                return true; // Negative cycle found
            }
        }
    }

    return false; // No negative cycle found
}
