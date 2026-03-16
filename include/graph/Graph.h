#pragma once

#include "IGraphStorage.h"

#include <memory>
#include <vector>

class Graph {
public:
    Graph();
    explicit Graph(std::unique_ptr<IGraphStorage> storage);

    void addVertex(int vertex);
    bool hasVertex(int vertex) const;

    void addEdge(int from, int to);
    bool hasEdge(int from, int to) const;

    const std::vector<int>& getNeighbors(int vertex) const;
    std::vector<int> getVertices() const;

    int vertexCount() const;
    int edgeCount() const;

private:
    std::unique_ptr<IGraphStorage> storage_;
};