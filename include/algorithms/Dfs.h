#pragma once

#include "../graph/Graph.h"

#include <set>

class DfsVisitor {
public:
    virtual ~DfsVisitor() = default;

    virtual void startComponent(int) {
    }

    virtual void discoverVertex(int, int) {
    }

    virtual void examineEdge(int, int) {
    }

    virtual void finishVertex(int, int) {
    }
};

class Dfs {
public:
    static void run(const Graph& graph, DfsVisitor& visitor);
    static void runFrom(const Graph& graph, int start, DfsVisitor& visitor);

private:
    static void dfs(const Graph& graph, int vertex, int parent, std::set<int>& used, DfsVisitor& visitor);
};