#include "../include/graph/Graph.h"
#include "../include/metrics/ConnectedComponentsMetric.h"
#include "catch_amalgamated.hpp"

TEST_CASE("Connected components in empty graph", "[metrics]") {
    Graph graph;
    ConnectedComponentsMetric metric;

    REQUIRE(metric.calculate(graph) == 0);
}

TEST_CASE("Connected components in graph with isolated vertices", "[metrics]") {
    Graph graph;
    ConnectedComponentsMetric metric;

    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);

    REQUIRE(metric.calculate(graph) == 3);
}

TEST_CASE("Connected components in connected graph", "[metrics]") {
    Graph graph;
    ConnectedComponentsMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    REQUIRE(metric.calculate(graph) == 1);
}

TEST_CASE("Connected components in graph with two components", "[metrics]") {
    Graph graph;
    ConnectedComponentsMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(3, 4);

    REQUIRE(metric.calculate(graph) == 2);
}

TEST_CASE("Connected components count mixed graph correctly", "[metrics]") {
    Graph graph;
    ConnectedComponentsMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addVertex(4);
    graph.addEdge(5, 6);

    REQUIRE(metric.calculate(graph) == 3);
}