#include "../../include/graph/AdjacencyListStorage.h"

#include <algorithm>
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

    if (hasEdge(from, to)) {
        return;
    }

    adjacency_[from].push_back(to);
    adjacency_[to].push_back(from);
    ++edge_count_;
}

bool AdjacencyListStorage::hasEdge(int from, int to) const {
    if (!hasVertex(from) || !hasVertex(to)) {
        return false;
    }

    const std::vector<int>& neighbors = adjacency_.at(from);
    return std::find(neighbors.begin(), neighbors.end(), to) != neighbors.end();
}

const std::vector<int>& AdjacencyListStorage::getNeighbors(int vertex) const {
    if (!hasVertex(vertex)) {
        throw std::out_of_range("Vertex does not exist");
    }

    return adjacency_.at(vertex);
}

std::vector<int> AdjacencyListStorage::getVertices() const {
    std::vector<int> vertices;

    for (const auto& pair : adjacency_) {
        vertices.push_back(pair.first);
    }

    return vertices;
}

int AdjacencyListStorage::vertexCount() const {
    return static_cast<int>(adjacency_.size());
}

int AdjacencyListStorage::edgeCount() const {
    return edge_count_;
}