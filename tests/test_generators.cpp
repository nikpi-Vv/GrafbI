#include "../include/generators/BasicGenerators.h"
#include "../include/metrics/Metrics.h"
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

TEST_CASE("Star graph generator creates correct graph", "[generators]") {
    StarGraphGenerator generator(5);
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
    REQUIRE(articulation_metric.calculate(graph) == 1);
}

TEST_CASE("Star graph with one vertex is valid", "[generators]") {
    StarGraphGenerator generator(1);
    Graph graph = generator.generate();

    REQUIRE(graph.vertexCount() == 1);
    REQUIRE(graph.edgeCount() == 0);
}

TEST_CASE("Wheel graph generator creates correct graph", "[generators]") {
    WheelGraphGenerator generator(6);
    Graph graph = generator.generate();

    ConnectedComponentsMetric components_metric;
    BridgesMetric bridges_metric;
    ArticulationPointsMetric articulation_metric;

    REQUIRE(graph.vertexCount() == 6);
    REQUIRE(graph.edgeCount() == 10);
    REQUIRE(components_metric.calculate(graph) == 1);
    REQUIRE(bridges_metric.calculate(graph) == 0);
    REQUIRE(articulation_metric.calculate(graph) == 0);
}

TEST_CASE("Wheel graph on four vertices is valid", "[generators]") {
    WheelGraphGenerator generator(4);
    Graph graph = generator.generate();

    REQUIRE(graph.vertexCount() == 4);
    REQUIRE(graph.edgeCount() == 6);
}

TEST_CASE("Wheel graph with one vertex is valid", "[generators]") {
    WheelGraphGenerator generator(1);
    Graph graph = generator.generate();

    REQUIRE(graph.vertexCount() == 1);
    REQUIRE(graph.edgeCount() == 0);
}

TEST_CASE("Complete bipartite graph generator creates correct graph", "[generators]") {
    CompleteBipartiteGraphGenerator generator(2, 3);
    Graph graph = generator.generate();

    BipartiteCheckMetric bipartite_metric;
    ConnectedComponentsMetric components_metric;
    BridgesMetric bridges_metric;
    ArticulationPointsMetric articulation_metric;
    DensityMetric density_metric;

    REQUIRE(graph.vertexCount() == 5);
    REQUIRE(graph.edgeCount() == 6);
    REQUIRE(bipartite_metric.calculate(graph));
    REQUIRE(components_metric.calculate(graph) == 1);
    REQUIRE(bridges_metric.calculate(graph) == 0);
    REQUIRE(articulation_metric.calculate(graph) == 0);
    REQUIRE(density_metric.calculate(graph) == Catch::Approx(0.6));
}

TEST_CASE("Complete bipartite graph with one and many vertices is a star", "[generators]") {
    CompleteBipartiteGraphGenerator generator(1, 4);
    Graph graph = generator.generate();

    BipartiteCheckMetric bipartite_metric;
    BridgesMetric bridges_metric;
    ArticulationPointsMetric articulation_metric;

    REQUIRE(graph.vertexCount() == 5);
    REQUIRE(graph.edgeCount() == 4);
    REQUIRE(bipartite_metric.calculate(graph));
    REQUIRE(bridges_metric.calculate(graph) == 4);
    REQUIRE(articulation_metric.calculate(graph) == 1);
}

TEST_CASE("Complete bipartite graph handles empty part", "[generators]") {
    CompleteBipartiteGraphGenerator generator(0, 3);
    Graph graph = generator.generate();

    REQUIRE(graph.vertexCount() == 3);
    REQUIRE(graph.edgeCount() == 0);
}

TEST_CASE("Complete bipartite graph with both empty parts is empty", "[generators]") {
    CompleteBipartiteGraphGenerator generator(0, 0);
    Graph graph = generator.generate();

    REQUIRE(graph.vertexCount() == 0);
    REQUIRE(graph.edgeCount() == 0);
}

TEST_CASE("Tree graph generator creates tree", "[generators]") {
    TreeGraphGenerator generator(7);
    Graph graph = generator.generate();

    ConnectedComponentsMetric components_metric;
    BridgesMetric bridges_metric;
    BipartiteCheckMetric bipartite_metric;

    REQUIRE(graph.vertexCount() == 7);
    REQUIRE(graph.edgeCount() == 6);
    REQUIRE(components_metric.calculate(graph) == 1);
    REQUIRE(bridges_metric.calculate(graph) == 6);
    REQUIRE(bipartite_metric.calculate(graph));
}

TEST_CASE("Tree graph generator handles empty graph", "[generators]") {
    TreeGraphGenerator generator(0);
    Graph graph = generator.generate();

    REQUIRE(graph.vertexCount() == 0);
    REQUIRE(graph.edgeCount() == 0);
}

TEST_CASE("Components graph generator creates required number of components", "[generators]") {
    ComponentsGraphGenerator generator(10, 3);
    Graph graph = generator.generate();

    ConnectedComponentsMetric components_metric;

    REQUIRE(graph.vertexCount() == 10);
    REQUIRE(components_metric.calculate(graph) == 3);
}

TEST_CASE("Components graph generator with one component is connected", "[generators]") {
    ComponentsGraphGenerator generator(6, 1);
    Graph graph = generator.generate();

    ConnectedComponentsMetric components_metric;
    REQUIRE(components_metric.calculate(graph) == 1);
}

TEST_CASE("Components graph generator with all isolated vertices works", "[generators]") {
    ComponentsGraphGenerator generator(5, 5);
    Graph graph = generator.generate();

    ConnectedComponentsMetric components_metric;
    REQUIRE(graph.edgeCount() == 0);
    REQUIRE(components_metric.calculate(graph) == 5);
}

TEST_CASE("Components graph generator handles empty graph", "[generators]") {
    ComponentsGraphGenerator generator(0, 0);
    Graph graph = generator.generate();

    REQUIRE(graph.vertexCount() == 0);
    REQUIRE(graph.edgeCount() == 0);
}

TEST_CASE("Bridges graph generator creates required number of bridges", "[generators]") {
    BridgesGraphGenerator generator(7, 3);
    Graph graph = generator.generate();

    BridgesMetric bridges_metric;
    REQUIRE(graph.vertexCount() == 7);
    REQUIRE(bridges_metric.calculate(graph) == 3);
}

TEST_CASE("Bridges graph generator with zero bridges works", "[generators]") {
    BridgesGraphGenerator generator(6, 0);
    Graph graph = generator.generate();

    BridgesMetric bridges_metric;
    REQUIRE(bridges_metric.calculate(graph) == 0);
}

TEST_CASE("Bridges graph generator can create tree", "[generators]") {
    BridgesGraphGenerator generator(5, 4);
    Graph graph = generator.generate();

    BridgesMetric bridges_metric;
    REQUIRE(bridges_metric.calculate(graph) == 4);
}

TEST_CASE("Articulation points graph generator creates required number of articulation points", "[generators]") {
    ArticulationPointsGraphGenerator generator(7, 3);
    Graph graph = generator.generate();

    ArticulationPointsMetric metric;
    REQUIRE(graph.vertexCount() == 7);
    REQUIRE(metric.calculate(graph) == 3);
}

TEST_CASE("Articulation points graph generator with zero articulation points works", "[generators]") {
    ArticulationPointsGraphGenerator generator(6, 0);
    Graph graph = generator.generate();

    ArticulationPointsMetric metric;
    REQUIRE(metric.calculate(graph) == 0);
}

TEST_CASE("Articulation points graph generator can create path like graph", "[generators]") {
    ArticulationPointsGraphGenerator generator(5, 3);
    Graph graph = generator.generate();

    ArticulationPointsMetric metric;
    REQUIRE(metric.calculate(graph) == 3);
}