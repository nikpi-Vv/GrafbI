#pragma once

#include <set>

class IGraphStorage {
public:
    virtual ~IGraphStorage() = default;

    virtual void addVertex(int vertex) = 0;
    virtual bool hasVertex(int vertex) const = 0;

    virtual void addEdge(int from, int to) = 0;
    virtual bool hasEdge(int from, int to) const = 0;

    virtual const std::set<int>& getNeighbors(int vertex) const = 0;
    virtual std::set<int> getVertices() const = 0;

    virtual int vertexCount() const = 0;
    virtual int edgeCount() const = 0;
};