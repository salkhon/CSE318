#include "RandomHeuristic.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>

RandomHeuristic::RandomHeuristic(CSPPtrWk csp_ptrwk):
    VariableOrderHeuristic{ csp_ptrwk } {
    std::srand(std::time(nullptr));
}

VariablePtr RandomHeuristic::next_var() {
    CSPPtr csp_ptr = csp_ptrwk.lock();
    std::vector<VariablePtr> unassigned_var_ptrs;
    
    for (VariablePtr var_ptr : csp_ptr->get_all_var_ptrs()) {
        if (!var_ptr->is_assigned()) {
            unassigned_var_ptrs.push_back(var_ptr);
        }
    }

    int randn = std::rand() % unassigned_var_ptrs.size();
    return unassigned_var_ptrs[randn];
}