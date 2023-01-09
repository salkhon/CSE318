#pragma once
#include "../Variable/Variable.hpp"
#include "../ConstraintGraph/ConstraintGraph.hpp"

/**
 * @brief Abstract class for getting next unassigned variable given the current state of the CSP.
 */
struct VariableOrderHeuristic {
    VariableOrderHeuristic(ConstraintGraphPtrWk);
    virtual VariablePtr next_var() = 0;
protected:
    const ConstraintGraphPtrWk constraint_graph_ptrwk;
};

int degree(const VariablePtr, const ConstraintGraphPtr);

using VOHPtr = std::shared_ptr<VariableOrderHeuristic>;