#pragma once

#include "../graph/Graph.h"

class DensityMetric {
public:
    double calculate(const Graph& graph) const;
};