/*
ID: 212487144
Email: nbashar4@gmail.com
*/

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <iostream>

class Algorithms
{
public:
    static bool isConnected(Graph &g);
    static std::vector<int> shortestPath(Graph &g, int start, int end);
    static std::vector<int> isContainsCycle(Graph &g);
    static std::pair<std::vector<int> ,std::vector<int>> isBipartite(Graph &g);
    static std::vector<int> negativeCycle(Graph &g);
};

#endif // ALGORITHMS_HPP