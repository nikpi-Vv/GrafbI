CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -Iexternal/catch2

GRAPH_SRC = src/graph/AdjacencyListStorage.cpp \
            src/graph/Graph.cpp \
            src/algorithms/Dfs.cpp \
            src/metrics/ConnectedComponentsMetric.cpp \
            src/metrics/DensityMetric.cpp \
            src/metrics/BipartiteCheckMetric.cpp \
            src/metrics/BridgesMetric.cpp

TEST_SRC = tests/test_main.cpp \
           tests/test_graph.cpp \
           external/catch2/catch_amalgamated.cpp \
		   

TEST_BIN = bin/tests.exe

all: tests

tests: $(TEST_BIN)

$(TEST_BIN): $(GRAPH_SRC) $(TEST_SRC)
	if not exist bin mkdir bin
	$(CXX) $(CXXFLAGS) $(GRAPH_SRC) $(TEST_SRC) -o $(TEST_BIN)

run-tests: $(TEST_BIN)
	$(TEST_BIN)

clean:
	if exist bin rmdir /s /q bin

.PHONY: all tests run-tests clean