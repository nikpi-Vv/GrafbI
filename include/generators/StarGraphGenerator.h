#pragma once

#include "IGraphGenerator.h"

class StarGraphGenerator : public IGraphGenerator {
public:
    explicit StarGraphGenerator(int vertex_count);

    Graph generate() const override;

private:
    int vertex_count_;
};