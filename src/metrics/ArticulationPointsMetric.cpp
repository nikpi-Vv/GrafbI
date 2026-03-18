#include "../../include/metrics/ArticulationPointsMetric.h"

#include <map>
#include <set>

namespace {
    void dfsArticulation(
        const Graph& graph,
        int vertex,
        int parent,
        std::set<int>& used,
        std::map<int, int>& tin,
        std::map<int, int>& low,
        std::set<int>& articulation_points,
        int& timer
    ) {
        used.insert(vertex);
        tin[vertex] = timer;
        low[vertex] = timer;
        ++timer;

        int children = 0;
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
                dfsArticulation(graph, to, vertex, used, tin, low, articulation_points, timer);

                if (low[to] < low[vertex]) {
                    low[vertex] = low[to];
                }

                if (parent != -1 && low[to] >= tin[vertex]) {
                    articulation_points.insert(vertex);
                }

                ++children;
            }
        }

        if (parent == -1 && children > 1) {
            articulation_points.insert(vertex);
        }
    }
}

int ArticulationPointsMetric::calculate(const Graph& graph) const {
    std::set<int> used;
    std::map<int, int> tin;
    std::map<int, int> low;
    std::set<int> articulation_points;
    std::set<int> vertices = graph.getVertices();

    int timer = 0;

    for (int vertex : vertices) {
        if (used.find(vertex) == used.end()) {
            dfsArticulation(graph, vertex, -1, used, tin, low, articulation_points, timer);
        }
    }

    return static_cast<int>(articulation_points.size());
}