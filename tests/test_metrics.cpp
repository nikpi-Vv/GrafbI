#include "../include/graph/Graph.h"
#include "../include/metrics/ConnectedComponentsMetric.h"
#include "../include/metrics/DensityMetric.h"
#include "../include/metrics/BipartiteCheckMetric.h"
#include "../include/metrics/BridgesMetric.h"
#include "../include/metrics/ArticulationPointsMetric.h"
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

TEST_CASE("Density of empty graph is zero", "[metrics]") {
    Graph graph;
    DensityMetric metric;

    REQUIRE(metric.calculate(graph) == Catch::Approx(0.0));
}

TEST_CASE("Density of graph with one vertex is zero", "[metrics]") {
    Graph graph;
    DensityMetric metric;

    graph.addVertex(1);

    REQUIRE(metric.calculate(graph) == Catch::Approx(0.0));
}

TEST_CASE("Density of complete graph with two vertices is one", "[metrics]") {
    Graph graph;
    DensityMetric metric;

    graph.addEdge(1, 2);

    REQUIRE(metric.calculate(graph) == Catch::Approx(1.0));
}

TEST_CASE("Density of path on three vertices", "[metrics]") {
    Graph graph;
    DensityMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);

    REQUIRE(metric.calculate(graph) == Catch::Approx(2.0 / 3.0));
}

TEST_CASE("Density of complete graph on four vertices is one", "[metrics]") {
    Graph graph;
    DensityMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);

    REQUIRE(metric.calculate(graph) == Catch::Approx(1.0));
}

TEST_CASE("Empty graph is bipartite", "[metrics]") {
    Graph graph;
    BipartiteCheckMetric metric;

    REQUIRE(metric.calculate(graph));
}

TEST_CASE("Graph with isolated vertices is bipartite", "[metrics]") {
    Graph graph;
    BipartiteCheckMetric metric;

    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);

    REQUIRE(metric.calculate(graph));
}

TEST_CASE("Path graph is bipartite", "[metrics]") {
    Graph graph;
    BipartiteCheckMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    REQUIRE(metric.calculate(graph));
}

TEST_CASE("Even cycle is bipartite", "[metrics]") {
    Graph graph;
    BipartiteCheckMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 1);

    REQUIRE(metric.calculate(graph));
}

TEST_CASE("Triangle is not bipartite", "[metrics]") {
    Graph graph;
    BipartiteCheckMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);

    REQUIRE_FALSE(metric.calculate(graph));
}

TEST_CASE("Mixed graph with non bipartite component is not bipartite", "[metrics]") {
    Graph graph;
    BipartiteCheckMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);

    graph.addEdge(4, 5);

    REQUIRE_FALSE(metric.calculate(graph));
}
 TEST_CASE("Empty graph has no bridges", "[metrics]") {
    Graph graph;
    BridgesMetric metric;

    REQUIRE(metric.calculate(graph) == 0);
}

TEST_CASE("Single edge graph has one bridge", "[metrics]") {
    Graph graph;
    BridgesMetric metric;

    graph.addEdge(1, 2);

    REQUIRE(metric.calculate(graph) == 1);
}

TEST_CASE("Path graph on four vertices has three bridges", "[metrics]") {
    Graph graph;
    BridgesMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    REQUIRE(metric.calculate(graph) == 3);
}

TEST_CASE("Triangle graph has no bridges", "[metrics]") {
    Graph graph;
    BridgesMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);

    REQUIRE(metric.calculate(graph) == 0);
}

TEST_CASE("Graph with one cycle tail has one bridge", "[metrics]") {
    Graph graph;
    BridgesMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);
    graph.addEdge(3, 4);

    REQUIRE(metric.calculate(graph) == 1);
}

TEST_CASE("Two components are processed correctly for bridges", "[metrics]") {
    Graph graph;
    BridgesMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(4, 5);
    graph.addEdge(5, 6);
    graph.addEdge(6, 4);

    REQUIRE(metric.calculate(graph) == 2);
}
TEST_CASE("Empty graph has no articulation points", "[metrics]") {
    Graph graph;
    ArticulationPointsMetric metric;

    REQUIRE(metric.calculate(graph) == 0);
}

TEST_CASE("Single vertex graph has no articulation points", "[metrics]") {
    Graph graph;
    ArticulationPointsMetric metric;

    graph.addVertex(1);

    REQUIRE(metric.calculate(graph) == 0);
}

TEST_CASE("Single edge graph has no articulation points", "[metrics]") {
    Graph graph;
    ArticulationPointsMetric metric;

    graph.addEdge(1, 2);

    REQUIRE(metric.calculate(graph) == 0);
}

TEST_CASE("Path graph on four vertices has two articulation points", "[metrics]") {
    Graph graph;
    ArticulationPointsMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    REQUIRE(metric.calculate(graph) == 2);
}

TEST_CASE("Triangle graph has no articulation points", "[metrics]") {
    Graph graph;
    ArticulationPointsMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);

    REQUIRE(metric.calculate(graph) == 0);
}

TEST_CASE("Star graph has one articulation point", "[metrics]") {
    Graph graph;
    ArticulationPointsMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(1, 5);

    REQUIRE(metric.calculate(graph) == 1);
}

TEST_CASE("Graph with cycle tail has one articulation point", "[metrics]") {
    Graph graph;
    ArticulationPointsMetric metric;

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);
    graph.addEdge(3, 4);

    REQUIRE(metric.calculate(graph) == 1);
}