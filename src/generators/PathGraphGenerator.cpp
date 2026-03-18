#include "../../include/generators/PathGraphGenerator.h"

#include <stdexcept>

PathGraphGenerator::PathGraphGenerator(int vertex_count) : vertex_count_(vertex_count) {
    if (vertex_count_ < 0) {
        throw std::invalid_argument("Vertex count must not be negative");
    }
}

Graph PathGraphGenerator::generate() const {
    Graph graph;

    for (int vertex = 1; vertex <= vertex_count_; ++vertex) {
        graph.addVertex(vertex);
    }

    for (int vertex = 1; vertex < vertex_count_; ++vertex) {
        graph.addEdge(vertex, vertex + 1);
    }

    return graph;
}