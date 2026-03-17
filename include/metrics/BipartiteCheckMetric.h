#pragma once

#include "../graph/Graph.h"

class BipartiteCheckMetric {
public:
    bool calculate(const Graph& graph) const;
};