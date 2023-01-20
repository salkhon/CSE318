#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "../Variable/Variable.hpp"

struct ConstraintGraph {
    std::vector<VarPtr> var_ptrs;
    std::vector<std::vector<int>> adj_list;

    ConstraintGraph(const std::vector<VarPtr>&);

    void add_edge(int, int);
    bool is_adj(int, int);
    int degree(int);
};

using ConstraintGraphPtr = std::shared_ptr<ConstraintGraph>;
using ConstraintGraphPtrWk = std::weak_ptr<ConstraintGraph>;
