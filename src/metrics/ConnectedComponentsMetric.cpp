#include "../../include/metrics/ConnectedComponentsMetric.h"
#include "../../include/algorithms/Dfs.h"
#include "../../include/algorithms/DfsVisitor.h"

class ConnectedComponentsVisitor : public DfsVisitor {
public:
    void startComponent(int) override {
        ++count_;
    }

    int getCount() const {
        return count_;
    }

private:
    int count_ = 0;
};

int ConnectedComponentsMetric::calculate(const Graph& graph) const {
    ConnectedComponentsVisitor visitor;
    Dfs::run(graph, visitor);
    return visitor.getCount();
}