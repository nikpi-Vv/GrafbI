#include "../include/generators/BasicGenerators.h"
#include "../include/metrics/Metrics.h"
#include "../include/parsers/Parsers.h"
#include "../include/serializers/Serializers.h"

#include <iostream>
#include <stdexcept>
#include <string>

namespace {
    Graph generateGraph(const std::string& type, int size) {
        if (type == "complete") {
            CompleteGraphGenerator generator(size);
            return generator.generate();
        }

        if (type == "path") {
            PathGraphGenerator generator(size);
            return generator.generate();
        }

        if (type == "cycle") {
            CycleGraphGenerator generator(size);
            return generator.generate();
        }

        if (type == "star") {
            StarGraphGenerator generator(size);
            return generator.generate();
        }

        if (type == "wheel") {
            WheelGraphGenerator generator(size);
            return generator.generate();
        }

        throw std::invalid_argument("Unknown generator type");
    }

    Graph parseGraph(const std::string& type, const std::string& filename) {
        if (type == "edges") {
            EdgeListParser parser;
            return parser.parse(filename);
        }

        if (type == "matrix") {
            AdjacencyMatrixParser parser;
            return parser.parse(filename);
        }

        if (type == "dimacs") {
            DimacsParser parser;
            return parser.parse(filename);
        }

        throw std::invalid_argument("Unknown parser type");
    }

    void serializeGraph(const std::string& type, const Graph& graph, const std::string& filename) {
        if (type == "edges") {
            EdgesSerializer serializer;
            serializer.serialize(graph, filename);
            return;
        }

        if (type == "dot") {
            GraphVizSerializer serializer;
            serializer.serialize(graph, filename);
            return;
        }

        throw std::invalid_argument("Unknown serializer type");
    }

    void printMetric(const std::string& name, const Graph& graph) {
        if (name == "components") {
            ConnectedComponentsMetric metric;
            std::cout << metric.calculate(graph) << "\n";
            return;
        }

        if (name == "density") {
            DensityMetric metric;
            std::cout << metric.calculate(graph) << "\n";
            return;
        }

        if (name == "bipartite") {
            BipartiteCheckMetric metric;
            std::cout << (metric.calculate(graph) ? "true" : "false") << "\n";
            return;
        }

        if (name == "bridges") {
            BridgesMetric metric;
            std::cout << metric.calculate(graph) << "\n";
            return;
        }

        if (name == "articulation") {
            ArticulationPointsMetric metric;
            std::cout << metric.calculate(graph) << "\n";
            return;
        }

        throw std::invalid_argument("Unknown metric");
    }
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            std::cout << "Usage:\n";
            std::cout << "  app generate <type> <size> <serializer> <output>\n";
            std::cout << "  app metric <metric_name> <parser_type> <input>\n";
            return 0;
        }

        std::string command = argv[1];

        if (command == "generate") {
            if (argc != 6) {
                throw std::invalid_argument("Invalid generate command");
            }

            std::string type = argv[2];
            int size = std::stoi(argv[3]);
            std::string serializer_type = argv[4];
            std::string output = argv[5];

            Graph graph = generateGraph(type, size);
            serializeGraph(serializer_type, graph, output);

            return 0;
        }

        if (command == "metric") {
            if (argc != 5) {
                throw std::invalid_argument("Invalid metric command");
            }

            std::string metric_name = argv[2];
            std::string parser_type = argv[3];
            std::string input = argv[4];

            Graph graph = parseGraph(parser_type, input);
            printMetric(metric_name, graph);

            return 0;
        }

        throw std::invalid_argument("Unknown command");
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
}