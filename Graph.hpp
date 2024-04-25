/*
ID: 212487144
Email: nbashar4@gmail.com
*/
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

class Graph
{
private:
    std::vector<std::vector<int>> adjacencyMatrix;
    int numVertices;
    bool isDirected;

public:
    Graph();
    void loadGraph(const std::vector<std::vector<int>> &matrix);
    void printGraph();
    int getNumVertices();
    bool getIsDirected();
    std::vector<std::vector<int>> &getAdjacencyMatrix();
};

#endif // GRAPH_HPP
