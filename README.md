# Graph Algorithms

This project implements essential graph algorithms in C++, covering connectivity, shortest paths, cycle detection, bipartite graphs, and negative cycles.

## Graph Class 

### Overview
This is a simple C++ class named `Graph` designed to represent a graph using an adjacency matrix. The class provides basic functionalities for loading a graph, printing it, and accessing its properties.

### Class Members
- `adjacencyMatrix`: A 2D vector representing the adjacency matrix of the graph.
- `numVertices`: An integer representing the number of vertices in the graph.
- `isDirected`: A boolean indicating whether the graph is directed or undirected.

### Class Methods
1. `Graph()`: Default constructor to initialize the graph.
2. `loadGraph(const std::vector<std::vector<int>> &matrix)`: Method to load a graph by providing its adjacency matrix.
3. `printGraph()`: Method to print the adjacency matrix of the graph.
4. `getNumVertices()`: Method to get the number of vertices in the graph.
5. `getIsDirected()`: Method to check if the graph is directed or undirected.
6. `getAdjacencyMatrix()`: Method to get a reference to the adjacency matrix of the graph.

### Usage
To use this class, include the `Graph.hpp` header file in your C++ project. Instantiate an object of the `Graph` class and use its methods to perform operations on the graph.

Example:
```cpp
#include "Graph.hpp"
#include <iostream>

int main() {
    Graph myGraph;
    std::vector<std::vector<int>> adjacencyMatrix = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    myGraph.loadGraph(adjacencyMatrix);
    myGraph.printGraph();
    std::cout << "Number of vertices: " << myGraph.getNumVertices() << std::endl;
    std::cout << "Is Directed: " << std::boolalpha << myGraph.getIsDirected() << std::endl;
    return 0;
}
```

## Algorithms Class

The following algorithms are implemented:

- `isConnected(Graph& g)`: Determines whether the graph is connected or not. Returns a boolean value indicating connectivity.
- `shortestPath(Graph& g, int start, int end)`: Computes the shortest path between two nodes in the graph. Returns the shortest path as a vector if one exists, otherwise returns an empty vector.
- `isContainsCycle(Graph& g)`: Checks if the graph contains any cycles. Returns a vector representing the cycle if found, otherwise returns an empty vector.
- `isBipartite(Graph& g)`: Determines whether the graph is bipartite or not. Returns a pair of vectors representing the two partitions if bipartite, otherwise returns empty vectors.
- `negativeCycle(Graph& g)`: Checks if the graph contains a negative cycle. Returns a vector representing the negative cycle if found, otherwise returns an empty vector.

### Usage

Include the `Algorithms.hpp` header file in your project and create an instance of the `Graph` class. You can then call the static methods of the `Algorithms` class on your `Graph` instance.

```cpp
#include "Algorithms.hpp"

int main() {
    Graph myGraph;
    // Load graph...
    bool connected = Algorithms::isConnected(myGraph);
    std::vector<int> shortestPath = Algorithms::shortestPath(myGraph, start, end);
    std::vector<int> cycle = Algorithms::isContainsCycle(myGraph);
    auto bipartite = Algorithms::isBipartite(myGraph);
    std::vector<int> negativeCycle = Algorithms::negativeCycle(myGraph);
    return 0;
}
```


