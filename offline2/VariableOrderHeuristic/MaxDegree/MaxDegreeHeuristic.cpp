#include "MaxDegreeHeuristic.hpp"

MaxDegreeHeuristic::MaxDegreeHeuristic(CSPPtrWk csp_ptrwk):
    VariableOrderHeuristic{ csp_ptrwk } {
}

VariablePtr MaxDegreeHeuristic::next_var() {
    CSPPtr csp_ptr = csp_ptrwk.lock();
    std::vector<int> unassignned_count = this->get_unassigned_var_count_for_each_row_col();
    VariablePtr target_var_ptr = nullptr, curr_var_ptr;
    int target_degree = -1, curr_degree;

    for (size_t r = 0; r < csp_ptr->N; r++) {
        for (size_t c = 0; c < csp_ptr->N; c++) {
            curr_var_ptr = csp_ptr->get_variable(r, c);
            curr_degree = unassignned_count[r] + unassignned_count[csp_ptr->N + c] - 2;
            if (
                !curr_var_ptr->is_assigned() &&
                curr_degree > target_degree
                ) {
                target_degree = curr_degree;
                target_var_ptr = curr_var_ptr;
            }
        }
    }

    return target_var_ptr;
}

const std::vector<int> MaxDegreeHeuristic::get_unassigned_var_count_for_each_row_col() {
    CSPPtr csp_ptr = csp_ptrwk.lock();
    std::vector<int> unassigned_count(2 * csp_ptr->N);
    std::vector<ConstraintPtr> constraint_ptrs = csp_ptr->get_all_constraint_ptrs();

    for (size_t i = 0; i < 2 * csp_ptr->N; i++) {
        unassigned_count[i] = constraint_ptrs[i]->get_num_unassigned();
    }
    
    return unassigned_count;
}