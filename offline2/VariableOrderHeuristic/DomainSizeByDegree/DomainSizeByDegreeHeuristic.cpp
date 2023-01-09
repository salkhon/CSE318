#include "DomainSizeByDegreeHeuristic.hpp"
#include <limits>

DomainSizeByDegreeHeuristic::DomainSizeByDegreeHeuristic(const ConstraintGraphPtrWk constraint_graph_ptrwk):
    VariableOrderHeuristic{ constraint_graph_ptrwk } {
}


double DomainSizeByDegreeHeuristic::score(const VariablePtr var_ptr, const ConstraintGraphPtr constraint_graph_ptr) {
    return var_ptr->domain.size() / degree(var_ptr, this->constraint_graph_ptrwk.lock());
}

VariablePtr DomainSizeByDegreeHeuristic::next_var() {
    auto constraint_graph_ptr = this->constraint_graph_ptrwk.lock();
    VariablePtr target_var_ptr = nullptr;

    for (auto& var_ptr : constraint_graph_ptr->var_ptrs) {
        if (
            !var_ptr->is_assigned()
            &&
            (target_var_ptr == nullptr
                ||
                score(var_ptr, constraint_graph_ptr) < score(target_var_ptr, constraint_graph_ptr))
            ) {
            target_var_ptr = var_ptr;
        }
    }
    return target_var_ptr;
}

