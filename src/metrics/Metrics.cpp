#include "../../include/metrics/Metrics.h"
#include "../../include/algorithms/Dfs.h"

#include <map>
#include <queue>
#include <set>

class ConnectedComponentsVisitor : public DfsVisitor {
public:
    void startComponent(int) override {
        ++count_;
    }

    int getCount() const {
        return count_;
    }

private:
    int count_ = 0;
};

int ConnectedComponentsMetric::calculate(const Graph& graph) const {
    ConnectedComponentsVisitor visitor;
    Dfs::run(graph, visitor);
    return visitor.getCount();
}

double DensityMetric::calculate(const Graph& graph) const {
    int vertices = graph.vertexCount();
    int edges = graph.edgeCount();

    if (vertices < 2) {
        return 0.0;
    }

    return 2.0 * edges / (vertices * (vertices - 1));
}

bool BipartiteCheckMetric::calculate(const Graph& graph) const {
    std::map<int, int> color;
    std::set<int> vertices = graph.getVertices();

    for (int start : vertices) {
        if (color.find(start) != color.end()) {
            continue;
        }

        color[start] = 0;
        std::queue<int> q;
        q.push(start);

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();

            const std::set<int>& neighbors = graph.getNeighbors(vertex);

            for (int to : neighbors) {
                if (color.find(to) == color.end()) {
                    color[to] = 1 - color[vertex];
                    q.push(to);
                } else if (color[to] == color[vertex]) {
                    return false;
                }
            }
        }
    }

    return true;
}

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