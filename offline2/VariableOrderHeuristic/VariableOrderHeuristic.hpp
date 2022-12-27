#pragma once
#include "../defs.hpp"
#include "../Variable/Variable.hpp"
#include <memory>

/**
 * @brief Abstract class for getting next unassigned variable given the current state of the CSP. 
 */
struct VariableOrderHeuristic {
    VariableOrderHeuristic(ConstraintGraphPtrWk);
    virtual VariablePtr next_var() = 0;
protected:
    const ConstraintGraphPtrWk constraint_graph_ptrwk;
};