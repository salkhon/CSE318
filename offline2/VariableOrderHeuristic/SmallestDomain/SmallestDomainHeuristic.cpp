#include "SmallestDomainHeuristic.hpp"

SmallestDomainHeuristic::SmallestDomainHeuristic(const ConstraintGraphPtrWk constraint_graph_ptrwk):
    VariableOrderHeuristic{ constraint_graph_ptrwk } {
}

VariablePtr SmallestDomainHeuristic::next_var() {
    const auto constraint_graph_ptr = this->constraint_graph_ptrwk.lock();
    VariablePtr target_var_ptr = nullptr;

    for (auto& var_ptr : constraint_graph_ptr->var_ptrs) {
        if (
            !var_ptr->is_assigned()
            &&
            (target_var_ptr == nullptr
                ||
                var_ptr->domain.size() < target_var_ptr->domain.size())
            ) {
            target_var_ptr = var_ptr;
        }
    }
    return target_var_ptr;
}