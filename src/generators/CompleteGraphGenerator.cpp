#include "../../include/generators/CompleteGraphGenerator.h"

#include <stdexcept>

CompleteGraphGenerator::CompleteGraphGenerator(int vertex_count) : vertex_count_(vertex_count) {
    if (vertex_count_ < 0) {
        throw std::invalid_argument("Vertex count must not be negative");
    }
}

Graph CompleteGraphGenerator::generate() const {
    Graph graph;

    for (int vertex = 1; vertex <= vertex_count_; ++vertex) {
        graph.addVertex(vertex);
    }

    for (int from = 1; from <= vertex_count_; ++from) {
        for (int to = from + 1; to <= vertex_count_; ++to) {
            graph.addEdge(from, to);
        }
    }

    return graph;
}