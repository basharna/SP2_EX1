/*
ID: 212487144
Email: nbashar4@gmail.com
*/

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <iostream>

class Algorithms {
public:
    static int isConnected(Graph& g);
    static std::vector<int> shortestPath(Graph& g, int start, int end);
    static bool isContainsCycle(Graph& g);
    static bool isBipartite(Graph& g);
    static bool negativeCycle(Graph& g);
};

#endif // ALGORITHMS_HPP
