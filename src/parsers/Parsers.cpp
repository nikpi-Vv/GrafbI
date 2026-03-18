#include "../../include/parsers/Parsers.h"

#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>

//
// Edge list
//

Graph EdgeListParser::parse(const std::string& filename) const {
    std::ifstream input(filename);

    if (!input.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    Graph graph;
    int from = 0;
    int to = 0;

    while (input >> from >> to) {
        graph.addEdge(from, to);
    }

    if (!input.eof()) {
        throw std::runtime_error("Invalid edge list format");
    }

    return graph;
}

//
// Adjacency matrix
//

Graph AdjacencyMatrixParser::parse(const std::string& filename) const {
    std::ifstream input(filename);

    if (!input.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    Graph graph;

    int value = 0;
    int row = 1;

    while (true) {
        std::streampos pos = input.tellg();

        std::string line;
        if (!std::getline(input, line)) {
            break;
        }

        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);

        int col = 1;
        bool has_values = false;

        while (iss >> value) {
            has_values = true;

            if (value != 0 && value != 1) {
                throw std::runtime_error("Matrix must contain only 0 or 1");
            }

            if (value == 1 && col > row) {
                graph.addEdge(row, col);
            }

            ++col;
        }

        if (!has_values) {
            continue;
        }

        ++row;
    }

    return graph;
}

//
// DIMACS
//

Graph DimacsParser::parse(const std::string& filename) const {
    std::ifstream input(filename);

    if (!input.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    Graph graph;
    std::string line;

    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string type;

        iss >> type;

        if (type == "c") {
            continue;
        }

        if (type == "p") {
            continue;
        }

        if (type == "e") {
            int from = 0;
            int to = 0;

            if (!(iss >> from >> to)) {
                throw std::runtime_error("Invalid edge in DIMACS");
            }

            graph.addEdge(from, to);
        }
    }

    return graph;
}