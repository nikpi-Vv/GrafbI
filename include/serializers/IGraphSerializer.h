#pragma once

#include "../graph/Graph.h"

#include <string>

class IGraphSerializer {
public:
    virtual ~IGraphSerializer() = default;

    virtual void serialize(const Graph& graph, const std::string& filename) const = 0;
};