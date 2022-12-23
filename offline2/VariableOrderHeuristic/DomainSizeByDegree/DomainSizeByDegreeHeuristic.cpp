#include "DomainSizeByDegreeHeuristic.hpp"

VariablePtr DomainSizeByDegreeHeuristic::next_var() {
    VariablePtr next;
    for (VariablePtr var_ptr : this->csp_ptr->get_all_var_ptrs()) {
        if (!var_ptr->is_assigned()) {
            // have to go through constraints to get degree
        }
    }
}