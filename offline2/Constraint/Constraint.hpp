#pragma once
#include "../defs.hpp"
#include <vector>
#include <memory>
/**
 * @brief Assigned variables in `var_ptrs` have to be unique.
 */
struct Constraint {
    Constraint(std::vector<VariablePtr>, CSPPtr);
    bool holds();
    int get_num_unassigned();
private:
    std::vector<VariablePtr> var_ptrs;
    CSPPtr csp_ptr;
};