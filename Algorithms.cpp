/*
ID: 7144
Email: nbashar4@gmail.com
*/

#include "Algorithms.hpp"
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>
using namespace std;

bool Algorithms::isConnected(Graph &g)
{
    vector<bool> visited(g.getNumVertices(), false);
    queue<int> q;
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
        {
            cout << "0" << endl;
            return false; // If any vertex is not visited, graph is not connected
        }
    }
    cout << "1" << endl;
    return true; // All vertices are visited, graph is connected
}

vector<int> Algorithms::shortestPath(Graph &g, int start, int end)
{
    if (start == end)
    {
        cout << "0" << endl;
        return {}; // Start and end are the same, return "0"
    }
    vector<int> dist(g.getNumVertices(), numeric_limits<int>::max());
    vector<int> prev(g.getNumVertices(), -1);
    dist[start] = 0;
    queue<int> q;
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

    if (dist[end] == numeric_limits<int>::max())
    {
        cout << "-1" << endl;
        return {}; // No path found, return "-1"
    }

    // print path
    vector<int> path;
    for (int at = end; at != -1; at = prev[at])
    {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    for (size_t i = 0; i < path.size(); ++i)
    {
        cout << path[i];
        if (i != path.size() - 1)
        {
            cout << "->";
        }
    }
    cout << endl;
    return path;
}

bool isDirectedCycleUtil(Graph &g, int v, vector<bool> &visited, vector<bool> &recStack, vector<int> &cycle)
{
    visited[v] = true;
    recStack[v] = true;

    for (int u = 0; u < g.getNumVertices(); ++u)
    {
        if (g.getAdjacencyMatrix()[v][u])
        {
            if (!visited[u])
            {
                if (isDirectedCycleUtil(g, u, visited, recStack, cycle))
                {
                    cycle.push_back(u);
                    return true;
                }
            }
            else if (recStack[u])
            {
                cycle.push_back(u);
                return true; // Cycle detected
            }
        }
    }

    recStack[v] = false; // Backtrack
    return false;
}

vector<int> isDirectedCycle(Graph &g)
{
    vector<bool> visited(g.getNumVertices(), false);
    vector<bool> recStack(g.getNumVertices(), false);
    vector<int> cycle;

    for (int v = 0; v < g.getNumVertices(); ++v)
    {
        if (!visited[v])
        {
            if (isDirectedCycleUtil(g, v, visited, recStack, cycle))
            {
                cycle.push_back(v);
                // Print the cycle
                cout << "The cycle is: " << cycle.back();
                for (int i = cycle.size() - 2; i >= 0; --i)
                {
                    cout << "->" << cycle[i];
                }
                cout << endl;
                reverse(cycle.begin(), cycle.end());
                return cycle;
            }
        }
    }
    cout << "0" << endl;
    return {};
}

bool isUndirectedCycleUtil(Graph &g, int v, int parent, vector<bool> &visited, vector<int> &cycle)
{
    visited[v] = true;

    for (int u = 0; u < g.getNumVertices(); ++u)
    {
        if (g.getAdjacencyMatrix()[v][u])
        {
            if (!visited[u])
            {
                if (isUndirectedCycleUtil(g, u, v, visited, cycle))
                {
                    cycle.push_back(u);
                    return true;
                }
            }
            else if (u != parent)
            {
                cycle.push_back(u);
                return true; // Cycle detected
            }
        }
    }

    return false;
}

vector<int> isUndirectedCycle(Graph &g)
{
    vector<bool> visited(g.getNumVertices(), false);
    vector<int> cycle;

    for (int v = 0; v < g.getNumVertices(); ++v)
    {
        if (!visited[v])
        {
            if (isUndirectedCycleUtil(g, v, -1, visited, cycle))
            {
                cycle.push_back(v);
                // Print the cycle
                cout << "The cycle is: " << cycle.back();
                for (int i = cycle.size() - 2; i >= 0; --i)
                {
                    cout << "->" << cycle[i];
                }
                cout << endl;
                reverse(cycle.begin(), cycle.end());
                return cycle;
            }
        }
    }
    cout << "0" << endl;
    return {};
}

vector<int> Algorithms::isContainsCycle(Graph &g)
{
    if (g.getIsDirected())
    {
        return isDirectedCycle(g);
    }
    else
    {
        return isUndirectedCycle(g);
    }
}

pair<vector<int>, vector<int>> Algorithms::isBipartite(Graph &g)
{
    vector<int> colors(g.getNumVertices(), -1);
    queue<int> q;

    for (int u = 0; u < g.getNumVertices(); ++u)
    {
        if (colors[u] != -1)
        {
            continue;
        }
        colors[u] = 1;
        q.push(u);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int v = 0; v < g.getNumVertices(); ++v)
            {
                if (g.getAdjacencyMatrix()[u][v] && colors[v] == -1)
                {
                    colors[v] = 1 - colors[u];
                    q.push(v);
                }
                else if (g.getAdjacencyMatrix()[u][v] && colors[v] == colors[u])
                {
                    cout << "0" << endl;
                    return {{}, {}}; // Not bipartite
                }
            }
        }
    }

    // Store the bipartite sets
    vector<int> setA, setB;
    for (int i = 0; i < g.getNumVertices(); ++i)
    {
        if (colors[i] == 1)
        {
            setA.push_back(i);
        }
        else if (colors[i] == 0)
        {
            setB.push_back(i);
        }
    }

    // Print the sets
    cout << "The graph is bipartite: ";
    cout << "A={";
    for (size_t i = 0; i < setA.size(); ++i)
    {
        cout << setA[i];
        if (i != setA.size() - 1)
        {
            cout << ",";
        }
    }
    cout << "}, B={";
    for (size_t i = 0; i < setB.size(); ++i)
    {
        cout << setB[i];
        if (i != setB.size() - 1)
        {
            cout << ",";
        }
    }
    cout << "}" << endl;

    return {setA, setB};
}

vector<int> Algorithms::negativeCycle(Graph &g)
{
    vector<int> dist(g.getNumVertices(), numeric_limits<int>::max());
    vector<int> prev(g.getNumVertices(), -1); // Add the prev vector

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
                    prev[v] = u; // Update the prev vector
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
                vector<int> cycle;
                int start = v;
                while (true)
                {
                    cycle.push_back(start);
                    start = prev[start];
                    if (start == v)
                    {
                        break;
                    }
                }
                reverse(cycle.begin(), cycle.end());
                for (size_t i = 0; i < cycle.size(); ++i)
                {
                    cout << cycle[i];
                    if (i != cycle.size() - 1)
                    {
                        cout << "->";
                    }
                }
                cout << endl;
                return cycle; // Negative cycle found
            }
        }
    }

    return {}; // No negative cycle found
}
