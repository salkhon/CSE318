#pragma once
#include "../definitions.hpp"

struct ConstructiveHeuristic {
    const ConstraintGraphPtrWk con_graph_ptrwk;
    ConstructiveHeuristic(const ConstraintGraphPtrWk);
    virtual std::vector<VarPtr> get_var_order() = 0;
};