#include "SmallestDomainHeuristic.hpp"
#include <limits>

SmallestDomainHeuristic::SmallestDomainHeuristic(CSPPtrWk csp_ptrwk): VariableOrderHeuristic{ csp_ptrwk } {
}

VariablePtr SmallestDomainHeuristic::next_var() {
    CSPPtr csp_ptr = csp_ptrwk.lock();
    VariablePtr target_var_ptr = nullptr;
    int target_dom_sz = std::numeric_limits<int>::max(), curr_dom_sz;

    for (VariablePtr var_ptr : csp_ptr->get_all_var_ptrs()) {
        curr_dom_sz = var_ptr->domain.size();
        if (!var_ptr->is_assigned() && curr_dom_sz < target_dom_sz) {
            target_var_ptr = var_ptr;
            target_dom_sz = curr_dom_sz;
        }
    }
    
    return target_var_ptr;
}