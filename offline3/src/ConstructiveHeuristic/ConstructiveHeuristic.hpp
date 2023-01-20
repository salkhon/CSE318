#pragma once
#include <vector>
#include <memory>

#include "../Variable/Variable.hpp"
#include "../ConstraintGraph/ConstraintGraph.hpp"

struct ConstructiveHeuristic {
    ConstraintGraphPtrWk con_graph_ptrwk;
    
    ConstructiveHeuristic(const ConstraintGraphPtrWk);
    virtual std::vector<VarPtr> get_var_order() = 0;
};

using ConHeuPtr = std::shared_ptr<ConstructiveHeuristic>;