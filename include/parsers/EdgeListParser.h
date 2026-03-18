#pragma once

#include "IGraphParser.h"

class EdgeListParser : public IGraphParser {
public:
    Graph parse(const std::string& filename) const override;
};