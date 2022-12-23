#include "RandomHeuristic.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>

RandomHeuristic::RandomHeuristic(CSPPtr csp_ptr):
    VariableOrderHeuristic{ csp_ptr } {
    std::srand(std::time(nullptr));
}

VariablePtr RandomHeuristic::next_var() {
    std::vector<VariablePtr> unassigned_var_ptrs;
    for (VariablePtr var_ptr : this->csp_ptr->get_all_var_ptrs()) {
        if (!var_ptr->is_assigned()) {
            unassigned_var_ptrs.push_back(var_ptr);
        }
    }

    int randn = std::rand() % unassigned_var_ptrs.size();
    return unassigned_var_ptrs[randn];
}