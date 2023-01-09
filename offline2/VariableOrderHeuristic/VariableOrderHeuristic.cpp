#include "VariableOrderHeuristic.hpp"

VariableOrderHeuristic::VariableOrderHeuristic(const ConstraintGraphPtrWk constraint_graph_ptrwk):
    constraint_graph_ptrwk{ constraint_graph_ptrwk } {
}

int degree(const VariablePtr var_ptr, const ConstraintGraphPtr constraint_graph_ptr) {
    return constraint_graph_ptr->var_graph[var_ptr->id].size();
}