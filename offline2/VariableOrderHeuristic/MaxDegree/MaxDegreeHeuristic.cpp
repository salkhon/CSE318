#include "MaxDegreeHeuristic.hpp"

VariablePtr MaxDegreeHeuristic::next_var() {
    std::vector<int> unassignned_count = this->get_unassigned_var_count_for_each_row_col();
    VariablePtr max_degree_var_ptr = nullptr;
    int max_degree = -1;
    for (size_t r = 0; r < this->csp_ptr->N; r++) {
        for (size_t c = 0; c < this->csp_ptr->N; c++) {
            if (!this->csp_ptr->get_variable(r, c)->is_assigned() &&
                (unassignned_count[r] + unassignned_count[c] - 2 > max_degree)) {
                max_degree_var_ptr = this->csp_ptr->get_variable(r, c);
            }
        }
    }
    return max_degree_var_ptr;
}

const std::vector<int> MaxDegreeHeuristic::get_unassigned_var_count_for_each_row_col() {
    std::vector<int> unassigned_count(2 * this->csp_ptr->N);
    std::vector<ConstraintPtr> constraint_ptrs = this->csp_ptr->get_all_constraint_ptrs();
    for (size_t i = 0; i < 2 * this->csp_ptr->N; i++) {
        unassigned_count[i] = constraint_ptrs[i]->get_num_unassigned();
    }
    return unassigned_count;
}
