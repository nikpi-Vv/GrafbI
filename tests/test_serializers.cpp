#include "../include/serializers/Serializers.h"
#include "../include/generators/BasicGenerators.h"
#include "catch_amalgamated.hpp"

#include <fstream>
#include <sstream>
#include <string>

namespace {
    std::string readFile(const std::string& filename) {
        std::ifstream input(filename);
        std::ostringstream buffer;
        buffer << input.rdbuf();
        return buffer.str();
    }
}

TEST_CASE("Edges serializer writes graph edges", "[serializers]") {
    PathGraphGenerator generator(4);
    Graph graph = generator.generate();

    EdgesSerializer serializer;
    const std::string filename = "test_graph.edges";

    serializer.serialize(graph, filename);

    std::string content = readFile(filename);

    REQUIRE(content.find("1 2") != std::string::npos);
    REQUIRE(content.find("2 3") != std::string::npos);
    REQUIRE(content.find("3 4") != std::string::npos);
}

TEST_CASE("Edges serializer writes empty graph", "[serializers]") {
    Graph graph;
    EdgesSerializer serializer;
    const std::string filename = "test_empty.edges";

    serializer.serialize(graph, filename);

    std::string content = readFile(filename);

    REQUIRE(content.empty());
}

TEST_CASE("GraphViz serializer writes graph structure", "[serializers]") {
    PathGraphGenerator generator(3);
    Graph graph = generator.generate();

    GraphVizSerializer serializer;
    const std::string filename = "test_graph.dot";

    serializer.serialize(graph, filename);

    std::string content = readFile(filename);

    REQUIRE(content.find("graph G") != std::string::npos);
    REQUIRE(content.find("1;") != std::string::npos);
    REQUIRE(content.find("2;") != std::string::npos);
    REQUIRE(content.find("3;") != std::string::npos);
    REQUIRE(content.find("1 -- 2") != std::string::npos);
    REQUIRE(content.find("2 -- 3") != std::string::npos);
}

TEST_CASE("GraphViz serializer writes empty graph", "[serializers]") {
    Graph graph;
    GraphVizSerializer serializer;
    const std::string filename = "test_empty.dot";

    serializer.serialize(graph, filename);

    std::string content = readFile(filename);

    REQUIRE(content.find("graph G") != std::string::npos);
}

TEST_CASE("Adjacency list serializer writes adjacency list", "[serializers]") {
    CycleGraphGenerator generator(4);
    Graph graph = generator.generate();

    AdjacencyListSerializer serializer;
    const std::string filename = "test_adj.txt";

    serializer.serialize(graph, filename);

    std::string content = readFile(filename);

    REQUIRE(content.find("1: 2 4") != std::string::npos);
    REQUIRE(content.find("2: 1 3") != std::string::npos);
    REQUIRE(content.find("3: 2 4") != std::string::npos);
    REQUIRE(content.find("4: 1 3") != std::string::npos);
}