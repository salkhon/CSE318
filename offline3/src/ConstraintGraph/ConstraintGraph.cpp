#include "ConstraintGraph.hpp"
#include <iostream>

ConstraintGraph::ConstraintGraph(const std::vector<VarPtr>& var_ptrs)
    : var_ptrs{ var_ptrs }, adj_list{ var_ptrs.size(), std::vector<int>() } {
}

void ConstraintGraph::add_edge(int v1, int v2) {
    if (std::find(this->adj_list[v1].begin(), this->adj_list[v1].end(), v2) == this->adj_list[v1].end()) {
        // if its true for c1 is true, its true for c2
        this->adj_list[v1].push_back(v2);
        this->adj_list[v2].push_back(v1);
    }
}

bool ConstraintGraph::is_adj(int v1, int v2) {
    return std::find(this->adj_list[v1].begin(), this->adj_list[v1].end(), v2) != this->adj_list[v1].end();
}

int ConstraintGraph::degree(int v) {
    return this->adj_list[v].size();
}
