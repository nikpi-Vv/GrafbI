#include "../../include/algorithms/Dfs.h"

#include <stdexcept>

void Dfs::run(const Graph& graph, DfsVisitor& visitor) {
    std::set<int> used;
    std::set<int> vertices = graph.getVertices();

    for (int vertex : vertices) {
        if (used.find(vertex) == used.end()) {
            visitor.startComponent(vertex);
            dfs(graph, vertex, -1, used, visitor);
        }
    }
}

void Dfs::runFrom(const Graph& graph, int start, DfsVisitor& visitor) {
    if (!graph.hasVertex(start)) {
        throw std::out_of_range("Start vertex does not exist");
    }

    std::set<int> used;
    visitor.startComponent(start);
    dfs(graph, start, -1, used, visitor);
}

void Dfs::dfs(const Graph& graph, int vertex, int parent, std::set<int>& used, DfsVisitor& visitor) {
    used.insert(vertex);
    visitor.discoverVertex(vertex, parent);

    const std::set<int>& neighbors = graph.getNeighbors(vertex);

    for (int to : neighbors) {
        visitor.examineEdge(vertex, to);

        if (used.find(to) == used.end()) {
            dfs(graph, to, vertex, used, visitor);
        }
    }

    visitor.finishVertex(vertex, parent);
}