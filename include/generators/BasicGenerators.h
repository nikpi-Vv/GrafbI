#pragma once

#include "IGraphGenerator.h"

class CompleteGraphGenerator : public IGraphGenerator {
public:
    explicit CompleteGraphGenerator(int vertex_count);

    Graph generate() const override;

private:
    int vertex_count_;
};

class PathGraphGenerator : public IGraphGenerator {
public:
    explicit PathGraphGenerator(int vertex_count);

    Graph generate() const override;

private:
    int vertex_count_;
};

class CycleGraphGenerator : public IGraphGenerator {
public:
    explicit CycleGraphGenerator(int vertex_count);

    Graph generate() const override;

private:
    int vertex_count_;
};

class StarGraphGenerator : public IGraphGenerator {
public:
    explicit StarGraphGenerator(int vertex_count);

    Graph generate() const override;

private:
    int vertex_count_;
};

class WheelGraphGenerator : public IGraphGenerator {
public:
    explicit WheelGraphGenerator(int vertex_count);

    Graph generate() const override;

private:
    int vertex_count_;
};

class CompleteBipartiteGraphGenerator : public IGraphGenerator {
public:
    CompleteBipartiteGraphGenerator(int left_size, int right_size);

    Graph generate() const override;

private:
    int left_size_;
    int right_size_;
};

class TreeGraphGenerator : public IGraphGenerator {
public:
    explicit TreeGraphGenerator(int vertex_count);

    Graph generate() const override;

private:
    int vertex_count_;
};

class ComponentsGraphGenerator : public IGraphGenerator {
public:
    ComponentsGraphGenerator(int vertex_count, int component_count);

    Graph generate() const override;

private:
    int vertex_count_;
    int component_count_;
};