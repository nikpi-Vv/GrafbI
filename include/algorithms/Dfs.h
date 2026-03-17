#pragma once

#include "../graph/Graph.h"
#include "DfsVisitor.h"

#include <set>

class Dfs {
public:
    static void run(const Graph& graph, DfsVisitor& visitor);
    static void runFrom(const Graph& graph, int start, DfsVisitor& visitor);

private:
    static void dfs(const Graph& graph, int vertex, int parent, std::set<int>& used, DfsVisitor& visitor);
};