#pragma once
#include <vector>
#include <memory>
#include <algorithm>

#include "../Variable/Variable.hpp"

struct ConstraintGraph {
    std::vector<VarPtr> var_ptrs;
    std::vector<std::vector<int>> nconflicts; // number of conflicts for a particular pair
    std::vector<std::vector<int>> adj_list;

    ConstraintGraph(const std::vector<VarPtr>&);

    void add_edge(int, int);
    bool is_adj(int, int);
    int degree(int);
    int nconflicts_for_pair(int, int);
};

using ConstraintGraphPtr = std::shared_ptr<ConstraintGraph>;
using ConstraintGraphPtrWk = std::weak_ptr<ConstraintGraph>;
