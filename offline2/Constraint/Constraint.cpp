#include "Constraint.hpp"
#include <algorithm>

Constraint::Constraint(std::vector<VariablePtr> var_ptrs, CSPPtr csp_ptr):
    var_ptrs{ var_ptrs }, csp_ptr{ csp_ptr } {
}

/**
 * @brief Check if the constraint holds by checking the value assigned for each constituent variables.
 *
 * @return true if all the ASSIGNED variables are unique and within [1, N]
 * @return false otherwise
 */
bool Constraint::holds() {
    std::vector<bool> is_val_assigned(this->csp_ptr->N, false);
    for (VariablePtr var_ptr : this->var_ptrs) {
        if (!var_ptr->is_assigned()) {
            continue;
        }

        if (is_val_assigned[var_ptr->val - 1]) {
            return false; // non unique assignment found
        } else {
            is_val_assigned[var_ptr->val - 1] = true;
        }
    }
    return true;
}

int Constraint::get_num_unassigned() {
    return std::count_if(this->var_ptrs.begin(), this->var_ptrs.end(), [](VariablePtr var_ptr) {
        return !var_ptr->is_assigned();
        });
}
