#include "../../include/serializers/Serializers.h"

#include <fstream>
#include <set>
#include <stdexcept>

void EdgesSerializer::serialize(const Graph& graph, const std::string& filename) const {
    std::ofstream output(filename);

    if (!output.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::set<int> vertices = graph.getVertices();

    for (int from : vertices) {
        const std::set<int>& neighbors = graph.getNeighbors(from);

        for (int to : neighbors) {
            if (from < to) {
                output << from << " " << to << "\n";
            }
        }
    }
}

void GraphVizSerializer::serialize(const Graph& graph, const std::string& filename) const {
    std::ofstream output(filename);

    if (!output.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    output << "graph G {\n";

    std::set<int> vertices = graph.getVertices();

    for (int vertex : vertices) {
        output << "    " << vertex << ";\n";
    }

    for (int from : vertices) {
        const std::set<int>& neighbors = graph.getNeighbors(from);

        for (int to : neighbors) {
            if (from < to) {
                output << "    " << from << " -- " << to << ";\n";
            }
        }
    }

    output << "}\n";
}

void AdjacencyListSerializer::serialize(const Graph& graph, const std::string& filename) const {
    std::ofstream output(filename);

    if (!output.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::set<int> vertices = graph.getVertices();

    for (int vertex : vertices) {
        output << vertex << ":";

        const std::set<int>& neighbors = graph.getNeighbors(vertex);

        if (!neighbors.empty()) {
            output << " ";
        }

        bool first = true;
        for (int neighbor : neighbors) {
            if (!first) {
                output << " ";
            }

            output << neighbor;
            first = false;
        }

        output << "\n";
    }
}