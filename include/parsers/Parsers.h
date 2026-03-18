#pragma once

#include "IGraphParser.h"

class EdgeListParser : public IGraphParser {
public:
    Graph parse(const std::string& filename) const override;
};

class AdjacencyMatrixParser : public IGraphParser {
public:
    Graph parse(const std::string& filename) const override;
};

class DimacsParser : public IGraphParser {
public:
    Graph parse(const std::string& filename) const override;
};