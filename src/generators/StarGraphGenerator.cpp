#include "../../include/generators/StarGraphGenerator.h"

#include <stdexcept>

StarGraphGenerator::StarGraphGenerator(int vertex_count) : vertex_count_(vertex_count) {
    if (vertex_count_ < 0) {
        throw std::invalid_argument("Vertex count must not be negative");
    }
}

Graph StarGraphGenerator::generate() const {
    Graph graph;

    for (int vertex = 1; vertex <= vertex_count_; ++vertex) {
        graph.addVertex(vertex);
    }

    for (int vertex = 2; vertex <= vertex_count_; ++vertex) {
        graph.addEdge(1, vertex);
    }

    return graph;
}