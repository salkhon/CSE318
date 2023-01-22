#pragma once
#include <vector>
#include <memory>

#include "../Variable/Variable.hpp"
#include "../ConstraintGraph/ConstraintGraph.hpp"

struct ConstructiveHeuristic {
    ConstraintGraphPtrWk constraint_graph_ptrwk;
    
    ConstructiveHeuristic(const ConstraintGraphPtrWk);
    virtual void assign_variables_in_order() = 0;

protected:
    std::vector<bool> days_assigned;
    int get_lowest_assignagble_day(VarPtr);
};

using ConHeuPtr = std::shared_ptr<ConstructiveHeuristic>;