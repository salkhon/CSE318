#pragma once
#include <vector>
#include <memory>
#include "../Variable/Variable.hpp"
#include "../Constraint/Constraint.hpp"
#include "../defs.hpp"

/**
 * @brief NxN variables of the board. 2N constraints for each row and column or variables. 
 */
struct CSP {
    const int N;

    CSP(int);
    VariablePtr get_variable(size_t, size_t);
    bool is_all_constraint_sat_so_far();
private:
    std::vector<VariablePtr> var_ptrs;
    std::vector<ConstraintPtr> constraint_ptrs;
};