#include "../../include/parsers/EdgeListParser.h"

#include <fstream>
#include <stdexcept>

Graph EdgeListParser::parse(const std::string& filename) const {
    std::ifstream input(filename);

    if (!input.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    Graph graph;
    int from = 0;
    int to = 0;

    while (input >> from >> to) {
        graph.addEdge(from, to);
    }

    if (!input.eof()) {
        throw std::runtime_error("Invalid edge list format");
    }

    return graph;
}