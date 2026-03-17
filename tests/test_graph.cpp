#include "../include/graph/Graph.h"
#include "catch_amalgamated.hpp"

TEST_CASE("Graph adds vertices", "[graph]") {
    Graph graph;

    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(1);

    REQUIRE(graph.vertexCount() == 2);
    REQUIRE(graph.hasVertex(1));
    REQUIRE(graph.hasVertex(2));
    REQUIRE_FALSE(graph.hasVertex(3));
}

TEST_CASE("Graph adds edges", "[graph]") {
    Graph graph;

    graph.addEdge(1, 2);

    REQUIRE(graph.vertexCount() == 2);
    REQUIRE(graph.edgeCount() == 1);
    REQUIRE(graph.hasEdge(1, 2));
    REQUIRE(graph.hasEdge(2, 1));
}

TEST_CASE("Graph does not add duplicate edges", "[graph]") {
    Graph graph;

    graph.addEdge(1, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 1);

    REQUIRE(graph.edgeCount() == 1);
}

TEST_CASE("Graph does not allow loops", "[graph]") {
    Graph graph;

    REQUIRE_THROWS(graph.addEdge(1, 1));
}

TEST_CASE("Graph returns neighbors", "[graph]") {
    Graph graph;

    graph.addEdge(1, 2);
    graph.addEdge(1, 3);

    const std::set<int>& neighbors = graph.getNeighbors(1);

    REQUIRE(neighbors.size() == 2);
    REQUIRE(neighbors.count(2) == 1);
    REQUIRE(neighbors.count(3) == 1);
}

TEST_CASE("Graph throws for missing vertex neighbors", "[graph]") {
    Graph graph;

    REQUIRE_THROWS(graph.getNeighbors(10));
}