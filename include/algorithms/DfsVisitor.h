#pragma once

class DfsVisitor {
public:
    virtual ~DfsVisitor() = default;

    virtual void startComponent(int vertex) {
    }

    virtual void discoverVertex(int vertex, int parent) {
    }

    virtual void examineEdge(int from, int to) {
    }

    virtual void finishVertex(int vertex, int parent) {
    }
};