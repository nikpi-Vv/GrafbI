#pragma once

#include "../graph/Graph.h"

class ConnectedComponentsMetric {
public:
    int calculate(const Graph& graph) const;
};

class DensityMetric {
public:
    double calculate(const Graph& graph) const;
};

class BipartiteCheckMetric {
public:
    bool calculate(const Graph& graph) const;
};

class BridgesMetric {
public:
    int calculate(const Graph& graph) const;
};

class ArticulationPointsMetric {
public:
    int calculate(const Graph& graph) const;
};