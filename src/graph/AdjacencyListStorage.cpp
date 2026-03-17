#include "../../include/graph/AdjacencyListStorage.h"

#include <stdexcept>

void AdjacencyListStorage::addVertex(int vertex) {
    if (vertex < 1) {
        throw std::invalid_argument("Vertex must be positive");
    }

    if (!hasVertex(vertex)) {
        adjacency_[vertex] = {};
    }
}

bool AdjacencyListStorage::hasVertex(int vertex) const {
    return adjacency_.find(vertex) != adjacency_.end();
}

void AdjacencyListStorage::addEdge(int from, int to) {
    if (from == to) {
        throw std::invalid_argument("Loops are not allowed");
    }

    addVertex(from);
    addVertex(to);

    if (!hasEdge(from, to)) {
        adjacency_[from].insert(to);
        adjacency_[to].insert(from);
        ++edge_count_;
    }
}

bool AdjacencyListStorage::hasEdge(int from, int to) const {
    if (!hasVertex(from) || !hasVertex(to)) {
        return false;
    }

    return adjacency_.at(from).find(to) != adjacency_.at(from).end();
}

const std::set<int>& AdjacencyListStorage::getNeighbors(int vertex) const {
    if (!hasVertex(vertex)) {
        throw std::out_of_range("Vertex does not exist");
    }

    return adjacency_.at(vertex);
}

std::set<int> AdjacencyListStorage::getVertices() const {
    std::set<int> vertices;

    for (const auto& pair : adjacency_) {
        vertices.insert(pair.first);
    }

    return vertices;
}

int AdjacencyListStorage::vertexCount() const {
    return static_cast<int>(adjacency_.size());
}

int AdjacencyListStorage::edgeCount() const {
    return edge_count_;
}