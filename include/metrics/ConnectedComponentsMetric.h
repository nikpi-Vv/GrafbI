#pragma once

#include "../graph/Graph.h"

class ConnectedComponentsMetric {
public:
    int calculate(const Graph& graph) const;
};