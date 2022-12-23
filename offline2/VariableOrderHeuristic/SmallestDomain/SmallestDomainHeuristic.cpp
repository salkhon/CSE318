#include "SmallestDomainHeuristic.hpp"

VariablePtr SmallestDomainHeuristic::next_var() {
    VariablePtr next = nullptr;
    for (VariablePtr var_ptr : this->csp_ptr->get_all_var_ptrs()) {
        if (!var_ptr->is_assigned() && (!next || next->domain.size() > var_ptr->domain.size())) {
            next = var_ptr;
        }
    }
    return next;
}