#include "Constraint.hpp"
#include <algorithm>

Constraint::Constraint(CSPPtr csp_ptr, std::vector<VariablePtr> var_ptrs):
    csp_ptr{ csp_ptr }, var_ptrs{ var_ptrs } {
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

// /**
//  * @brief Degree for the provided variable in this constraint. 
//  * 
//  * @param var_ptr Variable whose degree of involvement to check
//  * @return int Degree for provided variable, if variable not present in constraint degree is 0.
//  */
// int Constraint::degree_for(const VariablePtr var_ptr) {
//     int degree = 0;
//     if (std::find(this->var_ptrs.begin(), this->var_ptrs.end(), var_ptr) != this->var_ptrs.end()) {
//         // variable is in `this->var_ptrs`
//         for (VariablePtr var_neighbor : this->var_ptrs) {
//             if (var_neighbor != var_ptr && !var_neighbor->is_assigned()) {
//                 degree++;
//             }
//         }
//     }
//     return degree;
// }

int Constraint::get_num_unassigned() {
    return std::count_if(this->var_ptrs.begin(), this->var_ptrs.end(), [](VariablePtr var_ptr) {
        return !var_ptr->is_assigned();
    });
}
