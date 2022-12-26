#include "DomainSizeByDegreeHeuristic.hpp"
#include <limits>

DomainSizeByDegreeHeuristic::DomainSizeByDegreeHeuristic(CSPPtrWk csp_ptrwk)
    : VariableOrderHeuristic{ csp_ptrwk }, max_degree_heuristic{ csp_ptrwk } {
}

VariablePtr DomainSizeByDegreeHeuristic::next_var() {
    CSPPtr csp_ptr = csp_ptrwk.lock();
    std::vector<int> unassigned_count = this->max_degree_heuristic.get_unassigned_var_count_for_each_row_col();
    VariablePtr target_var_ptr, curr_var_ptr;
    double target_score = std::numeric_limits<double>::max(), curr_score;

    for (size_t i = 0; i < csp_ptr->N; i++) {
        for (size_t j = 0; j < csp_ptr->N; j++) {
            curr_var_ptr = csp_ptr->get_variable(i, j);
            curr_score =
                curr_var_ptr->domain.size() / (unassigned_count[i] + unassigned_count[csp_ptr->N + j] - 2);
            if (!curr_var_ptr->is_assigned() && curr_score < target_score) {
                target_score = curr_score;
                target_var_ptr = curr_var_ptr;
            }
        }
    }
    
    return target_var_ptr;
}