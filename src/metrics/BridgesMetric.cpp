#include "../../include/metrics/BridgesMetric.h"

#include <map>
#include <set>

namespace {
    void dfsBridge(
        const Graph& graph,
        int vertex,
        int parent,
        std::set<int>& used,
        std::map<int, int>& tin,
        std::map<int, int>& low,
        int& timer,
        int& bridges
    ) {
        used.insert(vertex);
        tin[vertex] = timer;
        low[vertex] = timer;
        ++timer;

        const std::set<int>& neighbors = graph.getNeighbors(vertex);

        for (int to : neighbors) {
            if (to == parent) {
                continue;
            }

            if (used.find(to) != used.end()) {
                if (tin[to] < low[vertex]) {
                    low[vertex] = tin[to];
                }
            } else {
                dfsBridge(graph, to, vertex, used, tin, low, timer, bridges);

                if (low[to] < low[vertex]) {
                    low[vertex] = low[to];
                }

                if (low[to] > tin[vertex]) {
                    ++bridges;
                }
            }
        }
    }
}

int BridgesMetric::calculate(const Graph& graph) const {
    std::set<int> used;
    std::map<int, int> tin;
    std::map<int, int> low;
    std::set<int> vertices = graph.getVertices();

    int timer = 0;
    int bridges = 0;

    for (int vertex : vertices) {
        if (used.find(vertex) == used.end()) {
            dfsBridge(graph, vertex, -1, used, tin, low, timer, bridges);
        }
    }

    return bridges;
}