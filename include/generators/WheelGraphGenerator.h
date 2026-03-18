#pragma once

#include "IGraphGenerator.h"

class WheelGraphGenerator : public IGraphGenerator {
public:
    explicit WheelGraphGenerator(int vertex_count);

    Graph generate() const override;

private:
    int vertex_count_;
};