#pragma once

#include "IGraphGenerator.h"

class PathGraphGenerator : public IGraphGenerator {
public:
    explicit PathGraphGenerator(int vertex_count);

    Graph generate() const override;

private:
    int vertex_count_;
};