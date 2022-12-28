#include "MaxDegreeHeuristic.hpp"

MaxDegreeHeuristic::MaxDegreeHeuristic(const ConstraintGraphPtrWk constraint_graph_ptrwk):
    VariableOrderHeuristic{ constraint_graph_ptrwk } {
}

int MaxDegreeHeuristic::degree(VariablePtr var_ptr) {
    return this->constraint_graph_ptrwk.lock()->var_graph[var_ptr->id].size();
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
                degree(var_ptr) > degree(target_var_ptr))
            ) {
            target_var_ptr = var_ptr;
        }
    }
    return target_var_ptr;
}
