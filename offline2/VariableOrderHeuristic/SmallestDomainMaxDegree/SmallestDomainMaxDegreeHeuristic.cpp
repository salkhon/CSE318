#include "SmallestDomainMaxDegreeHeuristic.hpp"
#include <limits>

SmallestDomainMaxDegreeHeuristic::SmallestDomainMaxDegreeHeuristic(CSPPtr csp_ptr):
    VariableOrderHeuristic{ csp_ptr }, max_degree_heuristic{ csp_ptr } {
}

VariablePtr SmallestDomainMaxDegreeHeuristic::next_var() {
    std::vector<int> unassigned_count = this->max_degree_heuristic.get_unassigned_var_count_for_each_row_col();
    VariablePtr target_var_ptr = nullptr, curr_var_ptr;
    int target_dom_sz = std::numeric_limits<int>::max(), target_degree = -1, curr_dom_sz, curr_degree;
    for (size_t i = 0; i < this->csp_ptr->N; i++) {
        for (size_t j = 0; j < this->csp_ptr->N; j++) {
            curr_var_ptr = this->csp_ptr->get_variable(i, j);
            curr_dom_sz = curr_var_ptr->domain.size();
            curr_degree = unassigned_count[i] + unassigned_count[this->csp_ptr->N + j] - 2;
            if (
                !curr_var_ptr->is_assigned() &&
                (curr_dom_sz < target_dom_sz || (curr_dom_sz == target_dom_sz && curr_degree > target_degree))
                ) {
                target_dom_sz = curr_dom_sz;
                target_degree = curr_degree;
                target_var_ptr = curr_var_ptr;
            }
        }
    }
    return target_var_ptr;
}