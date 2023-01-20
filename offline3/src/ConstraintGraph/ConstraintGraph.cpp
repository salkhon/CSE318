#include "ConstraintGraph.hpp"

ConstraintGraph::ConstraintGraph(const std::vector<VarPtr>& var_ptrs)
    : var_ptrs{ var_ptrs }, adj_list{ var_ptrs.size() } {
}

void ConstraintGraph::add_edge(int c1, int c2) {
    if (std::find(this->adj_list[c1].begin(), this->adj_list[c1].end(), c2) == this->adj_list[c1].end()) {
        // if its true for c1 is true, its true for c2
        this->adj_list[c1].push_back(c2);
        this->adj_list[c2].push_back(c1);
    }
}

bool ConstraintGraph::is_adj(int v1, int v2) {
    return std::find(this->adj_list[v1].begin(), this->adj_list[v1].end(), v2) != this->adj_list[v1].end();
}

int ConstraintGraph::degree(int v) {
    return this->adj_list[v].size();
}
