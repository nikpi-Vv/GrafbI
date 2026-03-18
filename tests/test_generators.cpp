#include "../include/generators/CompleteGraphGenerator.h"
#include "../include/generators/PathGraphGenerator.h"
#include "../include/generators/CycleGraphGenerator.h"
#include "../include/metrics/ConnectedComponentsMetric.h"
#include "../include/metrics/DensityMetric.h"
#include "../include/metrics/BipartiteCheckMetric.h"
#include "../include/metrics/BridgesMetric.h"
#include "../include/metrics/ArticulationPointsMetric.h"
#include "catch_amalgamated.hpp"

TEST_CASE("Complete graph generator creates correct graph", "[generators]") {
    CompleteGraphGenerator generator(4);
    Graph graph = generator.generate();

    DensityMetric density_metric;
    ConnectedComponentsMetric components_metric;
    BridgesMetric bridges_metric;
    ArticulationPointsMetric articulation_metric;

    REQUIRE(graph.vertexCount() == 4);
    REQUIRE(graph.edgeCount() == 6);
    REQUIRE(density_metric.calculate(graph) == Catch::Approx(1.0));
    REQUIRE(components_metric.calculate(graph) == 1);
    REQUIRE(bridges_metric.calculate(graph) == 0);
    REQUIRE(articulation_metric.calculate(graph) == 0);
}

TEST_CASE("Path graph generator creates correct graph", "[generators]") {
    PathGraphGenerator generator(5);
    Graph graph = generator.generate();

    BipartiteCheckMetric bipartite_metric;
    ConnectedComponentsMetric components_metric;
    BridgesMetric bridges_metric;
    ArticulationPointsMetric articulation_metric;

    REQUIRE(graph.vertexCount() == 5);
    REQUIRE(graph.edgeCount() == 4);
    REQUIRE(components_metric.calculate(graph) == 1);
    REQUIRE(bipartite_metric.calculate(graph));
    REQUIRE(bridges_metric.calculate(graph) == 4);
    REQUIRE(articulation_metric.calculate(graph) == 3);
}

TEST_CASE("Cycle graph generator creates correct graph", "[generators]") {
    CycleGraphGenerator generator(5);
    Graph graph = generator.generate();

    BipartiteCheckMetric bipartite_metric;
    ConnectedComponentsMetric components_metric;
    BridgesMetric bridges_metric;
    ArticulationPointsMetric articulation_metric;

    REQUIRE(graph.vertexCount() == 5);
    REQUIRE(graph.edgeCount() == 5);
    REQUIRE(components_metric.calculate(graph) == 1);
    REQUIRE_FALSE(bipartite_metric.calculate(graph));
    REQUIRE(bridges_metric.calculate(graph) == 0);
    REQUIRE(articulation_metric.calculate(graph) == 0);
}

TEST_CASE("Even cycle is bipartite", "[generators]") {
    CycleGraphGenerator generator(6);
    Graph graph = generator.generate();

    BipartiteCheckMetric bipartite_metric;

    REQUIRE(bipartite_metric.calculate(graph));
}

TEST_CASE("Generators handle zero vertices", "[generators]") {
    CompleteGraphGenerator complete_generator(0);
    PathGraphGenerator path_generator(0);
    CycleGraphGenerator cycle_generator(0);

    REQUIRE(complete_generator.generate().vertexCount() == 0);
    REQUIRE(path_generator.generate().vertexCount() == 0);
    REQUIRE(cycle_generator.generate().vertexCount() == 0);
}