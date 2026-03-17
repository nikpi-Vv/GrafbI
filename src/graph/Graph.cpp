#include "../../include/graph/Graph.h"
#include "../../include/graph/AdjacencyListStorage.h"

Graph::Graph() : storage_(std::make_unique<AdjacencyListStorage>()) {
}

Graph::Graph(std::unique_ptr<IGraphStorage> storage) : storage_(std::move(storage)) {
}

void Graph::addVertex(int vertex) {
    storage_->addVertex(vertex);
}

bool Graph::hasVertex(int vertex) const {
    return storage_->hasVertex(vertex);
}

void Graph::addEdge(int from, int to) {
    storage_->addEdge(from, to);
}

bool Graph::hasEdge(int from, int to) const {
    return storage_->hasEdge(from, to);
}

const std::set<int>& Graph::getNeighbors(int vertex) const {
    return storage_->getNeighbors(vertex);
}

std::set<int> Graph::getVertices() const {
    return storage_->getVertices();
}

int Graph::vertexCount() const {
    return storage_->vertexCount();
}

int Graph::edgeCount() const {
    return storage_->edgeCount();
}