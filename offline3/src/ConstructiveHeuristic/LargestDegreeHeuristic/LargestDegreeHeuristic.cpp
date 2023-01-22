#include "LargestDegreeHeuristic.hpp"
#include <iostream>

LargestDegreeHeuristic::LargestDegreeHeuristic(const ConstraintGraphPtrWk constraint_graph_ptrwk)
    : ConstructiveHeuristic{ constraint_graph_ptrwk } {
}

std::vector<VarPtr> get_var_order_degree(ConstraintGraphPtr constraint_graph_ptr) {
    std::vector<VarPtr> ordered_var_ptrs{constraint_graph_ptr->var_ptrs};

    std::sort(ordered_var_ptrs.begin(), ordered_var_ptrs.end(), 
        [constraint_graph_ptr](VarPtr v1, VarPtr v2) {
            return constraint_graph_ptr->degree(v1->id) > constraint_graph_ptr->degree(v2->id);
        }
    );
    
    return ordered_var_ptrs;
}

void LargestDegreeHeuristic::assign_variables_in_order() {
    auto constraint_graph_ptr = this->constraint_graph_ptrwk.lock();
    for (auto var_ptr : get_var_order_degree(constraint_graph_ptr)) {
        var_ptr->day = this->get_lowest_assignagble_day(var_ptr);
    }
}
