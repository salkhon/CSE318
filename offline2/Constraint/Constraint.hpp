#pragma once
#include "../defs.hpp"
#include <vector>
#include <memory>
/**
 * @brief Each constraint consists of N variables. It is true if N variables are unique in the range (1, N).
 */
struct Constraint {
    Constraint(CSPPtr, std::vector<VariablePtr>);
    bool holds();
private:
    std::vector<VariablePtr> var_ptrs;
    CSPPtr csp_ptr;
};