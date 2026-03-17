#pragma once

#include "IGraphStorage.h"

#include <map>
#include <set>

class AdjacencyListStorage : public IGraphStorage {
public:
    void addVertex(int vertex) override;
    bool hasVertex(int vertex) const override;

    void addEdge(int from, int to) override;
    bool hasEdge(int from, int to) const override;

    const std::set<int>& getNeighbors(int vertex) const override;
    std::set<int> getVertices() const override;

    int vertexCount() const override;
    int edgeCount() const override;

private:
    std::map<int, std::set<int>> adjacency_;
    int edge_count_ = 0;
};