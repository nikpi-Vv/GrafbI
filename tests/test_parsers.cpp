#include "../include/parsers/Parsers.h"
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

    REQUIRE(graph.vertexCount() == 4);
    REQUIRE(graph.edgeCount() == 3);
    REQUIRE(graph.hasEdge(1, 2));
    REQUIRE(graph.hasEdge(2, 3));
    REQUIRE(graph.hasEdge(3, 4));
}

TEST_CASE("Adjacency matrix parser works", "[parsers]") {
    const std::string filename = "test_matrix.txt";
    writeFile(filename,
        "0 1 0\n"
        "1 0 1\n"
        "0 1 0\n"
    );

    AdjacencyMatrixParser parser;
    Graph graph = parser.parse(filename);

    REQUIRE(graph.vertexCount() == 3);
    REQUIRE(graph.edgeCount() == 2);
}

TEST_CASE("DIMACS parser works", "[parsers]") {
    const std::string filename = "test_dimacs.txt";
    writeFile(filename,
        "c comment\n"
        "p edge 3 2\n"
        "e 1 2\n"
        "e 2 3\n"
    );

    DimacsParser parser;
    Graph graph = parser.parse(filename);

    REQUIRE(graph.vertexCount() == 3);
    REQUIRE(graph.edgeCount() == 2);
}