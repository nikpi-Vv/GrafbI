#pragma once

#include "../graph/Graph.h"

class ArticulationPointsMetric {
public:
    int calculate(const Graph& graph) const;
};