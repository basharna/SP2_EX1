/*
ID: 7144
Email: nbashar4@gmail.com
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Algorithms.hpp"
#include "Graph.hpp"
#include "doctest.h"

TEST_CASE("isConnected")
{
    SUBCASE("Connected Graph")
    {
        // Connected graph
        std::vector<std::vector<int>> adjacencyMatrix = {
            {0, 1, 1, 0},
            {1, 0, 0, 1},
            {1, 0, 0, 1},
            {0, 1, 1, 0}};
        Graph g;
        g.loadGraph(adjacencyMatrix);

        CHECK(Algorithms::isConnected(g) == true);
    }

    SUBCASE("Disconnected Graph")
    {
        // Disconnected graph
        std::vector<std::vector<int>> adjacencyMatrix = {
            {0, 1, 0, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 1},
            {0, 0, 1, 0}};
        Graph g;
        g.loadGraph(adjacencyMatrix);

        CHECK(Algorithms::isConnected(g) == false);
    }
}

TEST_CASE("shortestPath")
{
    // Graph with a known shortest path
    std::vector<std::vector<int>> adjacencyMatrix = {
        {0, 1, 0, 1},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}};
    Graph g;
    g.loadGraph(adjacencyMatrix);

    // Graph with weighted edges
    std::vector<std::vector<int>> adjacencyMatrixWeighted = {
        {0, 1, 0, 7},
        {0, 0, 2, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}};
    Graph gWeighted;
    gWeighted.loadGraph(adjacencyMatrixWeighted);

    SUBCASE("Shortest Path Exists")
    {
        std::vector<int> expectedPath = {0, 3};
        CHECK(Algorithms::shortestPath(g, 0, 3) == expectedPath);
        std::vector<int> expectedPathWeighted = {0, 1, 2, 3};
        CHECK(Algorithms::shortestPath(gWeighted, 0, 3) == expectedPathWeighted);
    }

    SUBCASE("No Shortest Path")
    {
        CHECK(Algorithms::shortestPath(g, 3, 0).empty());
        CHECK(Algorithms::shortestPath(g, 0, 0).empty());
        CHECK(Algorithms::shortestPath(gWeighted, 3, 0).empty());
    }
}

TEST_CASE("isContainsCycle")
{

    SUBCASE("Directed Cycle")
    {
        // Graph with a known cycle
        std::vector<std::vector<int>> adjacencyMatrix = {
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1},
            {1, 0, 0, 0}};
        Graph g;
        g.loadGraph(adjacencyMatrix);
        std::vector<int> expectedCycle = {0, 1, 2, 3, 0};
        CHECK(Algorithms::isContainsCycle(g) == expectedCycle);
    }

    SUBCASE("No Directed Cycle")
    {
        // Graph with no cycle
        std::vector<std::vector<int>> adjacencyMatrix = {
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1},
            {0, 0, 0, 0}};
        Graph g;
        g.loadGraph(adjacencyMatrix);
        CHECK(Algorithms::isContainsCycle(g).empty());
    }

    SUBCASE("Undirected Cycle")
    {
        // Undirected cycle
        std::vector<std::vector<int>> adjacencyMatrix = {
            {0, 1, 0, 1, 0, 0},
            {1, 0, 1, 0, 0, 0},
            {0, 1, 0, 1, 1, 1},
            {1, 0, 1, 0, 0, 0},
            {0, 0, 1, 0, 0, 0},
            {0, 0, 1, 0, 0, 0}};
        Graph g;
        g.loadGraph(adjacencyMatrix);

        std::vector<int> expectedCycle = {0, 1, 2, 3, 0};
        CHECK(Algorithms::isContainsCycle(g) == expectedCycle);
    }

    SUBCASE("No Undirected Cycle")
    {
        // Undirected graph with no cycle
        std::vector<std::vector<int>> adjacencyMatrix = {
            {0, 1, 0, 0, 0, 0},
            {1, 0, 1, 0, 0, 0},
            {0, 1, 0, 1, 0, 0},
            {0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 1},
            {0, 0, 0, 0, 1, 0}};
        Graph g;
        g.loadGraph(adjacencyMatrix);
        CHECK(Algorithms::isContainsCycle(g).empty());
    }
}

TEST_CASE("isBipartite")
{

    SUBCASE("Undirected Bipartite Graph")
    {
        // Bipartite graph
        std::vector<std::vector<int>> adjacencyMatrix = {
            {0, 1, 1, 0},
            {1, 0, 0, 1},
            {1, 0, 0, 1},
            {0, 1, 1, 0}};
        Graph g;
        g.loadGraph(adjacencyMatrix);

        std::pair<std::vector<int>, std::vector<int>> bipartiteSets = Algorithms::isBipartite(g);
        std::vector<int> &setA = bipartiteSets.first;
        std::vector<int> &setB = bipartiteSets.second;
        std::vector<int> expectedSetA = {0, 3}; // Vertices in one set
        std::vector<int> expectedSetB = {1, 2}; // Vertices in the other set
        CHECK(setA == expectedSetA);
        CHECK(setB == expectedSetB);
    }
    SUBCASE("Undirected Not Bipartite Graph")
    {
        // Not bipartite graph
        std::vector<std::vector<int>> adjacencyMatrix = {
            {0, 1, 2, 0, 0},
            {1, 0, 3, 0, 0},
            {2, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
        Graph g;
        g.loadGraph(adjacencyMatrix);

        std::pair<std::vector<int>, std::vector<int>> bipartiteSets = Algorithms::isBipartite(g);
        std::vector<int> &setA = bipartiteSets.first;
        std::vector<int> &setB = bipartiteSets.second;
        CHECK(setA.empty());
        CHECK(setB.empty());
    }

    SUBCASE("Directed Bipartite Graph")
    {
        std::vector<std::vector<int>> adjacencyMatrix = {
            {0, 0, 0, 0, 5, 0},
            {0, 0, 0, 0, 3, 0},
            {0, 0, 0, 11, 0, 5},
            {1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 11, 0, 0, 0, 0}};
        Graph g;
        g.loadGraph(adjacencyMatrix);

        std::pair<std::vector<int>, std::vector<int>> bipartiteSets = Algorithms::isBipartite(g);
        std::vector<int> &setA = bipartiteSets.first;
        std::vector<int> &setB = bipartiteSets.second;
        std::vector<int> expectedSetA = {0, 1, 2}; // Vertices in one set
        std::vector<int> expectedSetB = {3, 4, 5}; // Vertices in the other set
        CHECK(setA == expectedSetA);
        CHECK(setB == expectedSetB);
    }
}

TEST_CASE("negativeCycle")
{

    SUBCASE("Negative Cycle Exists")
    {
        // Graph with a negative cycle
        std::vector<std::vector<int>> adjacencyMatrix = {
            {0, 0, 0, 0},
            {4, 0, -6, 0},
            {0, 0, 0, 5},
            {0, -2, 0, 0}};

        Graph g;
        g.loadGraph(adjacencyMatrix);
        std::vector<int> expectedCycle = {3, 1, 2};
        CHECK(Algorithms::negativeCycle(g) == expectedCycle);
    }

    SUBCASE("No Negative Cycle")
    {
        // graph with no negative cycle
        std::vector<std::vector<int>> adjacencyMatrix = {
            {0, 0, 0, 6},
            {4, 0, 6, 0},
            {0, 0, 0, 0},
            {0, 2, 0, 0}};

        Graph g;
        g.loadGraph(adjacencyMatrix);
        CHECK(Algorithms::negativeCycle(g).empty());
    }
}

TEST_CASE("Invalid Graph")
{
    // Invalid graph
    std::vector<std::vector<int>> adjacencyMatrix = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    Graph g;
    CHECK_THROWS(g.loadGraph(adjacencyMatrix));
}