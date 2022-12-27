#include "SmallestDomainMaxDegreeHeuristic.hpp"

SmallestDomainMaxDegreeHeuristic::SmallestDomainMaxDegreeHeuristic(ConstraintGraphPtrWk constraint_graph_ptrwk):
    VariableOrderHeuristic{ constraint_graph_ptrwk } {
}

int SmallestDomainMaxDegreeHeuristic::degree(VariablePtr var_ptr) {
    return this->constraint_graph_ptrwk.lock()->var_graph[var_ptr->id].size();
}

VariablePtr SmallestDomainMaxDegreeHeuristic::next_var() {
    const auto constraint_graph_ptr = this->constraint_graph_ptrwk.lock();
    VariablePtr target_var_ptr = nullptr;
    
    for (auto& var_ptr : constraint_graph_ptr->var_ptrs) {
        if (
            !var_ptr->is_assigned()
            &&
            (target_var_ptr == nullptr
                ||
                (var_ptr->domain.size() < target_var_ptr->domain.size()
                    ||
                    var_ptr->domain.size() == target_var_ptr->domain.size() && degree(var_ptr) > degree(target_var_ptr)))
            ) {
            target_var_ptr = var_ptr;
        }
    }
    return target_var_ptr;
}
