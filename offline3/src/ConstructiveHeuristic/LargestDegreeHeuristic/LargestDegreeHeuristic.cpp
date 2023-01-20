#include "LargestDegreeHeuristic.hpp"
#include <iostream>

LargestDegreeHeuristic::LargestDegreeHeuristic(const ConstraintGraphPtrWk con_graph_ptrwk)
    : ConstructiveHeuristic{ con_graph_ptrwk } {
}

std::vector<VarPtr> LargestDegreeHeuristic::get_var_order() {
    auto con_graph_ptr = this->con_graph_ptrwk.lock();
    std::vector<VarPtr> ordered_var_ptrs{con_graph_ptr->var_ptrs};
    std::sort(ordered_var_ptrs.begin(), ordered_var_ptrs.end(), 
        [con_graph_ptr](VarPtr v1, VarPtr v2) {
            return con_graph_ptr->degree(v1->id) > con_graph_ptr->degree(v2->id);
        }
    );
    
    return ordered_var_ptrs;
}
