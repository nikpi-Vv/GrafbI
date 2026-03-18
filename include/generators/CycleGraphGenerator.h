#pragma once

#include "IGraphGenerator.h"

class CycleGraphGenerator : public IGraphGenerator {
public:
    explicit CycleGraphGenerator(int vertex_count);

    Graph generate() const override;

private:
    int vertex_count_;
};