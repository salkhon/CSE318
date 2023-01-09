#include "MaxDegreeHeuristic.hpp"

MaxDegreeHeuristic::MaxDegreeHeuristic(const ConstraintGraphPtrWk constraint_graph_ptrwk):
    VariableOrderHeuristic{ constraint_graph_ptrwk } {
}

VariablePtr MaxDegreeHeuristic::next_var() {
    const auto constraint_graph_ptr = this->constraint_graph_ptrwk.lock();
    VariablePtr target_var_ptr = nullptr;

    for (auto var_ptr : constraint_graph_ptr->var_ptrs) {
        if (
            !var_ptr->is_assigned()
            &&
            (target_var_ptr == nullptr
                ||
                degree(var_ptr, constraint_graph_ptr) > degree(target_var_ptr, constraint_graph_ptr))
            ) {
            target_var_ptr = var_ptr;
        }
    }
    return target_var_ptr;
}
