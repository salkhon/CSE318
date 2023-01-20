#include "LargestEnrollmentHeuristic.hpp"

LargestEnrollmentHeuristic::LargestEnrollmentHeuristic(const ConstraintGraphPtrWk con_graph_ptrwk)
    : ConstructiveHeuristic{ con_graph_ptrwk } {
}

std::vector<VarPtr> LargestEnrollmentHeuristic::get_var_order() {
    auto con_graph_ptr = this->con_graph_ptrwk.lock();
    std::vector<VarPtr> ordered_var_ptr{con_graph_ptr->var_ptrs};
    std::sort(ordered_var_ptr.begin(), ordered_var_ptr.end(), 
        [](VarPtr v1, VarPtr v2) {
            return v1->nstudents > v2->nstudents;
        }
    );
    return ordered_var_ptr;
}
