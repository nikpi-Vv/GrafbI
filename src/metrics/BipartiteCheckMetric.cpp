#include "../../include/metrics/BipartiteCheckMetric.h"

#include <map>
#include <queue>

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