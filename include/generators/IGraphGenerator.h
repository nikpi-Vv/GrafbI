#pragma once

#include "../graph/Graph.h"

class IGraphGenerator {
public:
    virtual ~IGraphGenerator() = default;

    virtual Graph generate() const = 0;
};