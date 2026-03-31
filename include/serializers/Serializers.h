#pragma once

#include "IGraphSerializer.h"

class EdgesSerializer : public IGraphSerializer {
public:
    void serialize(const Graph& graph, const std::string& filename) const override;
};

class GraphVizSerializer : public IGraphSerializer {
public:
    void serialize(const Graph& graph, const std::string& filename) const override;
};

class AdjacencyListSerializer : public IGraphSerializer {
public:
    void serialize(const Graph& graph, const std::string& filename) const override;
};