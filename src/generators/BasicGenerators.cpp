#include "../../include/generators/BasicGenerators.h"

#include <stdexcept>
#include <random>
#include <stdexcept>

CompleteGraphGenerator::CompleteGraphGenerator(int vertex_count) : vertex_count_(vertex_count) {
    if (vertex_count_ < 0) {
        throw std::invalid_argument("Vertex count must not be negative");
    }
}

Graph CompleteGraphGenerator::generate() const {
    Graph graph;

    for (int vertex = 1; vertex <= vertex_count_; ++vertex) {
        graph.addVertex(vertex);
    }

    for (int from = 1; from <= vertex_count_; ++from) {
        for (int to = from + 1; to <= vertex_count_; ++to) {
            graph.addEdge(from, to);
        }
    }

    return graph;
}

PathGraphGenerator::PathGraphGenerator(int vertex_count) : vertex_count_(vertex_count) {
    if (vertex_count_ < 0) {
        throw std::invalid_argument("Vertex count must not be negative");
    }
}

Graph PathGraphGenerator::generate() const {
    Graph graph;

    for (int vertex = 1; vertex <= vertex_count_; ++vertex) {
        graph.addVertex(vertex);
    }

    for (int vertex = 1; vertex < vertex_count_; ++vertex) {
        graph.addEdge(vertex, vertex + 1);
    }

    return graph;
}

CycleGraphGenerator::CycleGraphGenerator(int vertex_count) : vertex_count_(vertex_count) {
    if (vertex_count_ < 0) {
        throw std::invalid_argument("Vertex count must not be negative");
    }
}

Graph CycleGraphGenerator::generate() const {
    Graph graph;

    for (int vertex = 1; vertex <= vertex_count_; ++vertex) {
        graph.addVertex(vertex);
    }

    if (vertex_count_ <= 1) {
        return graph;
    }

    for (int vertex = 1; vertex < vertex_count_; ++vertex) {
        graph.addEdge(vertex, vertex + 1);
    }

    if (vertex_count_ > 2) {
        graph.addEdge(vertex_count_, 1);
    }

    return graph;
}

StarGraphGenerator::StarGraphGenerator(int vertex_count) : vertex_count_(vertex_count) {
    if (vertex_count_ < 0) {
        throw std::invalid_argument("Vertex count must not be negative");
    }
}

Graph StarGraphGenerator::generate() const {
    Graph graph;

    for (int vertex = 1; vertex <= vertex_count_; ++vertex) {
        graph.addVertex(vertex);
    }

    for (int vertex = 2; vertex <= vertex_count_; ++vertex) {
        graph.addEdge(1, vertex);
    }

    return graph;
}

WheelGraphGenerator::WheelGraphGenerator(int vertex_count) : vertex_count_(vertex_count) {
    if (vertex_count_ < 0) {
        throw std::invalid_argument("Vertex count must not be negative");
    }
}

Graph WheelGraphGenerator::generate() const {
    Graph graph;

    for (int vertex = 1; vertex <= vertex_count_; ++vertex) {
        graph.addVertex(vertex);
    }

    if (vertex_count_ <= 1) {
        return graph;
    }

    for (int vertex = 2; vertex < vertex_count_; ++vertex) {
        graph.addEdge(vertex, vertex + 1);
    }

    if (vertex_count_ > 2) {
        graph.addEdge(vertex_count_, 2);
    }

    for (int vertex = 2; vertex <= vertex_count_; ++vertex) {
        graph.addEdge(1, vertex);
    }

    return graph;
}

CompleteBipartiteGraphGenerator::CompleteBipartiteGraphGenerator(int left_size, int right_size)
    : left_size_(left_size), right_size_(right_size) {
    if (left_size_ < 0 || right_size_ < 0) {
        throw std::invalid_argument("Part size must not be negative");
    }
}

Graph CompleteBipartiteGraphGenerator::generate() const {
    Graph graph;

    int total = left_size_ + right_size_;

    for (int vertex = 1; vertex <= total; ++vertex) {
        graph.addVertex(vertex);
    }

    for (int left = 1; left <= left_size_; ++left) {
        for (int right = left_size_ + 1; right <= total; ++right) {
            graph.addEdge(left, right);
        }
    }

    return graph;
}

TreeGraphGenerator::TreeGraphGenerator(int vertex_count) : vertex_count_(vertex_count) {
    if (vertex_count_ < 0) {
        throw std::invalid_argument("Vertex count must not be negative");
    }
}

Graph TreeGraphGenerator::generate() const {
    Graph graph;

    for (int vertex = 1; vertex <= vertex_count_; ++vertex) {
        graph.addVertex(vertex);
    }

    for (int vertex = 2; vertex <= vertex_count_; ++vertex) {
        graph.addEdge(vertex / 2, vertex);
    }

    return graph;
}

ComponentsGraphGenerator::ComponentsGraphGenerator(int vertex_count, int component_count)
    : vertex_count_(vertex_count), component_count_(component_count) {
    if (vertex_count_ < 0) {
        throw std::invalid_argument("Vertex count must not be negative");
    }

    if (component_count_ < 0) {
        throw std::invalid_argument("Component count must not be negative");
    }

    if (component_count_ > vertex_count_) {
        throw std::invalid_argument("Component count must not exceed vertex count");
    }
}

Graph ComponentsGraphGenerator::generate() const {
    Graph graph;

    for (int vertex = 1; vertex <= vertex_count_; ++vertex) {
        graph.addVertex(vertex);
    }

    if (vertex_count_ == 0 || component_count_ == 0) {
        return graph;
    }

    int current = 1;
    int base_size = vertex_count_ / component_count_;
    int extra = vertex_count_ % component_count_;

    for (int component = 0; component < component_count_; ++component) {
        int size = base_size;

        if (extra > 0) {
            ++size;
            --extra;
        }

        for (int i = 0; i + 1 < size; ++i) {
            graph.addEdge(current + i, current + i + 1);
        }

        current += size;
    }

    return graph;
}

BridgesGraphGenerator::BridgesGraphGenerator(int vertex_count, int bridge_count)
    : vertex_count_(vertex_count), bridge_count_(bridge_count) {
    if (vertex_count_ < 0) {
        throw std::invalid_argument("Vertex count must not be negative");
    }

    if (bridge_count_ < 0) {
        throw std::invalid_argument("Bridge count must not be negative");
    }

    if (bridge_count_ > vertex_count_ - 1 && vertex_count_ > 0) {
        throw std::invalid_argument("Too many bridges for given vertex count");
    }
}

Graph BridgesGraphGenerator::generate() const {
    Graph graph;

    for (int vertex = 1; vertex <= vertex_count_; ++vertex) {
        graph.addVertex(vertex);
    }

    if (vertex_count_ == 0) {
        return graph;
    }

    int used_vertices = bridge_count_ + 1;

    if (used_vertices > vertex_count_) {
        throw std::invalid_argument("Too many bridges for given vertex count");
    }

    for (int vertex = 1; vertex <= bridge_count_; ++vertex) {
        graph.addEdge(vertex, vertex + 1);
    }

    if (used_vertices < vertex_count_) {
        int cycle_start = used_vertices;
        int cycle_end = vertex_count_;

        if (cycle_end - cycle_start + 1 >= 3) {
            for (int vertex = cycle_start; vertex < cycle_end; ++vertex) {
                graph.addEdge(vertex, vertex + 1);
            }
            graph.addEdge(cycle_end, cycle_start);
        } else {
            for (int vertex = used_vertices + 1; vertex <= vertex_count_; ++vertex) {
                graph.addEdge(used_vertices, vertex);
            }
        }
    }

    return graph;
}

ArticulationPointsGraphGenerator::ArticulationPointsGraphGenerator(int vertex_count, int articulation_count)
    : vertex_count_(vertex_count), articulation_count_(articulation_count) {
    if (vertex_count_ < 0) {
        throw std::invalid_argument("Vertex count must not be negative");
    }

    if (articulation_count_ < 0) {
        throw std::invalid_argument("Articulation count must not be negative");
    }

    if (vertex_count_ == 0 && articulation_count_ != 0) {
        throw std::invalid_argument("Too many articulation points for given vertex count");
    }

    if (vertex_count_ > 0 && articulation_count_ > vertex_count_ - 2) {
        throw std::invalid_argument("Too many articulation points for given vertex count");
    }
}

Graph ArticulationPointsGraphGenerator::generate() const {
    Graph graph;

    for (int vertex = 1; vertex <= vertex_count_; ++vertex) {
        graph.addVertex(vertex);
    }

    if (vertex_count_ == 0) {
        return graph;
    }

    if (articulation_count_ == 0) {
        if (vertex_count_ >= 3) {
            for (int vertex = 1; vertex < vertex_count_; ++vertex) {
                graph.addEdge(vertex, vertex + 1);
            }
            graph.addEdge(vertex_count_, 1);
        } else if (vertex_count_ == 2) {
            graph.addEdge(1, 2);
        }
        return graph;
    }

    int chain_vertices = articulation_count_ + 2;

    for (int vertex = 1; vertex < chain_vertices; ++vertex) {
        graph.addEdge(vertex, vertex + 1);
    }

    for (int vertex = chain_vertices + 1; vertex <= vertex_count_; ++vertex) {
        graph.addEdge(chain_vertices - 1, vertex);
        graph.addEdge(chain_vertices, vertex);
    }

    return graph;
}

CubicGraphGenerator::CubicGraphGenerator(int vertex_count) : vertex_count_(vertex_count) {
    if (vertex_count_ < 4) {
        throw std::invalid_argument("Cubic graph requires at least 4 vertices");
    }

    if (vertex_count_ % 2 != 0) {
        throw std::invalid_argument("Cubic graph requires even number of vertices");
    }
}

Graph CubicGraphGenerator::generate() const {
    Graph graph;

    for (int vertex = 1; vertex <= vertex_count_; ++vertex) {
        graph.addVertex(vertex);
    }

    for (int vertex = 1; vertex < vertex_count_; ++vertex) {
        graph.addEdge(vertex, vertex + 1);
    }
    graph.addEdge(vertex_count_, 1);

    int half = vertex_count_ / 2;
    for (int vertex = 1; vertex <= half; ++vertex) {
        graph.addEdge(vertex, vertex + half);
    }

    return graph;
}

RandomGraphGenerator::RandomGraphGenerator(int vertex_count, double probability)
    : vertex_count_(vertex_count), probability_(probability) {
    if (vertex_count_ < 0) {
        throw std::invalid_argument("Vertex count must not be negative");
    }

    if (probability_ < 0.0 || probability_ > 1.0) {
        throw std::invalid_argument("Probability must be between 0 and 1");
    }
}

Graph RandomGraphGenerator::generate() const {
    Graph graph;

    for (int vertex = 1; vertex <= vertex_count_; ++vertex) {
        graph.addVertex(vertex);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dist(probability_);

    for (int from = 1; from <= vertex_count_; ++from) {
        for (int to = from + 1; to <= vertex_count_; ++to) {
            if (dist(gen)) {
                graph.addEdge(from, to);
            }
        }
    }

    return graph;
}