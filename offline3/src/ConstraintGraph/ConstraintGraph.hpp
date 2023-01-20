#pragma once
#include "../definitions.hpp"

struct ConstraintGraph {
    std::vector<VarPtr> var_ptrs;
    std::vector<std::vector<int>> adj_list;

    ConstraintGraph(const std::vector<VarPtr>&);

    void add_edge(int, int);
    bool is_adj(int, int);
    int degree(int);
};