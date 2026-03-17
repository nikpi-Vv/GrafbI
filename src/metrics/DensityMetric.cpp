#include "../../include/metrics/DensityMetric.h"

double DensityMetric::calculate(const Graph& graph) const {
    int vertices = graph.vertexCount();
    int edges = graph.edgeCount();

    if (vertices < 2) {
        return 0.0;
    }

    return 2.0 * edges / (vertices * (vertices - 1));
}