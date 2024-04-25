/*
ID: 212487144
Email: nbashar4@gmail.com
*/
#include "Graph.hpp"
#include <iostream>

Graph::Graph() : numVertices(0) {}

void Graph::loadGraph(const std::vector<std::vector<int>>& matrix) {
    if (matrix.size() != matrix[0].size()) {
        throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
    }
    adjacencyMatrix = matrix;
    numVertices = matrix.size();

    // Check if the graph is directed or not
    isDirected = false;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (adjacencyMatrix[i][j] != adjacencyMatrix[j][i]) {
                isDirected = true;
                break;
            }
        }
    }
}

void Graph::printGraph() {
    int numEdges = 0;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (adjacencyMatrix[i][j] != 0) {
                numEdges++;
            }
        }
    }
    std::cout << "Graph with " << numVertices << " vertices and " << numEdges << " edges" << std::endl;
}

int Graph::getNumVertices() {
    return numVertices;
}

bool Graph::getIsDirected() {
    return isDirected;
}

std::vector<std::vector<int>>& Graph::getAdjacencyMatrix() {
    return adjacencyMatrix;
}
