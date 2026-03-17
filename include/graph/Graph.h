#pragma once

#include "IGraphStorage.h"

#include <memory>
#include <set>

class Graph {
public:
    Graph();
    explicit Graph(std::unique_ptr<IGraphStorage> storage);

    void addVertex(int vertex);
    bool hasVertex(int vertex) const;

    void addEdge(int from, int to);
    bool hasEdge(int from, int to) const;

    const std::set<int>& getNeighbors(int vertex) const;
    std::set<int> getVertices() const;

    int vertexCount() const;
    int edgeCount() const;

private:
    std::unique_ptr<IGraphStorage> storage_;
};