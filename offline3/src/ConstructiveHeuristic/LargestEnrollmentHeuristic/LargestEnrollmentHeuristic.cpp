#include "LargestEnrollmentHeuristic.hpp"

LargestEnrollmentHeuristic::LargestEnrollmentHeuristic(const ConstraintGraphPtrWk constraint_graph_ptrwk)
    : ConstructiveHeuristic{ constraint_graph_ptrwk } {
}


std::vector<VarPtr> get_var_order_enrollment(ConstraintGraphPtr constraint_graph_ptr) {
    std::vector<VarPtr> ordered_var_ptr{ constraint_graph_ptr->var_ptrs };

    std::sort(ordered_var_ptr.begin(), ordered_var_ptr.end(),
        [](VarPtr v1, VarPtr v2) {
            return v1->nstudents > v2->nstudents;
        }
    );

    return ordered_var_ptr;
}

void LargestEnrollmentHeuristic::assign_variables_in_order() {
    auto constraint_graph_ptr = this->constraint_graph_ptrwk.lock();
    for (auto var_ptr : get_var_order_enrollment(constraint_graph_ptr)) {
        var_ptr->day = this->get_lowest_assignagble_day(var_ptr);
    }
}
