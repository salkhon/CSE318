#include "RandomHeuristic.hpp"

RandomHeuristic::RandomHeuristic(const ConstraintGraphPtrWk constraint_graph_ptrwk)
    : ConstructiveHeuristic{ constraint_graph_ptrwk } {
}

std::vector<VarPtr> get_var_order(ConstraintGraphPtr constraint_graph_ptr) {
    std::vector<VarPtr> ordered_var_ptrs{ constraint_graph_ptr->var_ptrs };

    return ordered_var_ptrs;
}

void RandomHeuristic::assign_variables_in_order() {
    auto constraint_graph_ptr = this->constraint_graph_ptrwk.lock();
    for (auto var_ptr : get_var_order(constraint_graph_ptr)) {
        var_ptr->day = this->get_lowest_assignagble_day(var_ptr);
    }
}