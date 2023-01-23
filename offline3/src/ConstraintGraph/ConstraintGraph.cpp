#include "ConstraintGraph.hpp"
#include <iostream>

ConstraintGraph::ConstraintGraph(const std::vector<VarPtr>& var_ptrs)
    : var_ptrs{ var_ptrs }, adj_list{ var_ptrs.size(), std::vector<int>() },
    nconflicts(this->var_ptrs.size(), std::vector<int>(this->var_ptrs.size(), 0)) {
}

void ConstraintGraph::add_edge(int v1, int v2) {
    if (v1 > v2) {
        std::swap(v1, v2);
    }

    if (std::find(this->adj_list[v1].begin(), this->adj_list[v1].end(), v2) == this->adj_list[v1].end()) {
        // if its true for c1 is true, its true for c2
        this->adj_list[v1].push_back(v2);
        this->adj_list[v2].push_back(v1);
    }
    
    this->nconflicts[v1][v2]++;
}

bool ConstraintGraph::is_adj(int v1, int v2) {
    return std::find(this->adj_list[v1].begin(), this->adj_list[v1].end(), v2) != this->adj_list[v1].end();
}

int ConstraintGraph::degree(int v) {
    return this->adj_list[v].size();
}

int ConstraintGraph::nconflicts_for_pair(int v1, int v2) {
    if (v1 > v2) {
        std::swap(v1, v2);
    }
    return this->nconflicts[v1][v2];
}

std::ostream& operator<<(std::ostream& ostrm, const ConstraintGraph& constraint_graph) {
    ostrm << "Constraint Graph: \n";
    for (size_t v = 0; v < constraint_graph.var_ptrs.size(); v++) {
        ostrm << "\tVar " << v << "\t: ";
        for (auto n : constraint_graph.adj_list[v]) {
            ostrm << n << " ";
        }
        ostrm << "\n";
    }
    return ostrm;
}
