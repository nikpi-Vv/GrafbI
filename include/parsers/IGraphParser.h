#pragma once

#include "../graph/Graph.h"

#include <string>

class IGraphParser {
public:
    virtual ~IGraphParser() = default;

    virtual Graph parse(const std::string& filename) const = 0;
};