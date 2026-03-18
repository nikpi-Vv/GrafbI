#include "../../include/generators/WheelGraphGenerator.h"

#include <stdexcept>

WheelGraphGenerator::WheelGraphGenerator(int vertex_count) : vertex_count_(vertex_count) {
    if (vertex_count_ < 0) {
        throw std::invalid_argument("Vertex count must not be negative");
    }
}

Graph WheelGraphGenerator::generate() const {
    Graph graph;

    for (int vertex = 1; vertex <= vertex_count_; ++vertex) {
        graph.addVertex(vertex);
    }

    if (vertex_count_ <= 1) {
        return graph;
    }

    for (int vertex = 2; vertex < vertex_count_; ++vertex) {
        graph.addEdge(vertex, vertex + 1);
    }

    if (vertex_count_ > 2) {
        graph.addEdge(vertex_count_, 2);
    }

    for (int vertex = 2; vertex <= vertex_count_; ++vertex) {
        graph.addEdge(1, vertex);
    }

    return graph;
}