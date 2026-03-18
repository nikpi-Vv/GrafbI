#pragma once

#include "IGraphGenerator.h"

class CompleteGraphGenerator : public IGraphGenerator {
public:
    explicit CompleteGraphGenerator(int vertex_count);

    Graph generate() const override;

private:
    int vertex_count_;
};