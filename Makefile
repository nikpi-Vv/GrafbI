CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -Iexternal/catch2

GRAPH_SRC = src/graph/AdjacencyListStorage.cpp \
            src/graph/Graph.cpp

TEST_SRC = tests/test_main.cpp \
           tests/test_graph.cpp \
           external/catch2/catch_amalgamated.cpp

APP_SRC = app/main.cpp

TEST_BIN = bin/tests.exe
APP_BIN = bin/app.exe

all: tests app

tests: $(TEST_BIN)

app: $(APP_BIN)

$(TEST_BIN): $(GRAPH_SRC) $(TEST_SRC)
	if not exist bin mkdir bin
	$(CXX) $(CXXFLAGS) $(GRAPH_SRC) $(TEST_SRC) -o $(TEST_BIN)

$(APP_BIN): $(GRAPH_SRC) $(APP_SRC)
	if not exist bin mkdir bin
	$(CXX) $(CXXFLAGS) $(GRAPH_SRC) $(APP_SRC) -o $(APP_BIN)

run-tests: $(TEST_BIN)
	$(TEST_BIN)

run-app: $(APP_BIN)
	$(APP_BIN)

clean:
	if exist bin rmdir /s /q bin

.PHONY: all tests app run-tests run-app clean