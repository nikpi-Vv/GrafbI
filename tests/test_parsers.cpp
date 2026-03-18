#include "../include/parsers/EdgeListParser.h"
#include "../include/metrics/Metrics.h"
#include "catch_amalgamated.hpp"

#include <fstream>
#include <string>

namespace {
    void writeFile(const std::string& filename, const std::string& content) {
        std::ofstream output(filename);
        output << content;
    }
}

TEST_CASE("Edge list parser reads simple graph", "[parsers]") {
    const std::string filename = "test_edges_1.txt";
    writeFile(filename, "1 2\n2 3\n3 4\n");

    EdgeListParser parser;
    Graph graph = parser.parse(filename);

    ConnectedComponentsMetric components_metric;
    BridgesMetric bridges_metric;

    REQUIRE(graph.vertexCount() == 4);
    REQUIRE(graph.edgeCount() == 3);
    REQUIRE(graph.hasEdge(1, 2));
    REQUIRE(graph.hasEdge(2, 3));
    REQUIRE(graph.hasEdge(3, 4));
    REQUIRE(components_metric.calculate(graph) == 1);
    REQUIRE(bridges_metric.calculate(graph) == 3);
}

TEST_CASE("Edge list parser reads graph with repeated edges once", "[parsers]") {
    const std::string filename = "test_edges_2.txt";
    writeFile(filename, "1 2\n2 1\n1 2\n");

    EdgeListParser parser;
    Graph graph = parser.parse(filename);

    REQUIRE(graph.vertexCount() == 2);
    REQUIRE(graph.edgeCount() == 1);
    REQUIRE(graph.hasEdge(1, 2));
}

TEST_CASE("Edge list parser reads empty file", "[parsers]") {
    const std::string filename = "test_edges_3.txt";
    writeFile(filename, "");

    EdgeListParser parser;
    Graph graph = parser.parse(filename);

    REQUIRE(graph.vertexCount() == 0);
    REQUIRE(graph.edgeCount() == 0);
}

TEST_CASE("Edge list parser throws on invalid file", "[parsers]") {
    EdgeListParser parser;

    REQUIRE_THROWS(parser.parse("file_that_does_not_exist.txt"));
}

TEST_CASE("Edge list parser throws on invalid format", "[parsers]") {
    const std::string filename = "test_edges_4.txt";
    writeFile(filename, "1 2\n2 x\n");

    EdgeListParser parser;

    REQUIRE_THROWS(parser.parse(filename));
}