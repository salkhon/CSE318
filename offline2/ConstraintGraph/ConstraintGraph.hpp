#pragma once
#include "../defs.hpp"
#include <vector>
#include <memory>

/**
 * @brief Container for the variables and the uniqueness constraint graph between them.
 */
struct ConstraintGraph {
    std::vector<std::vector<int>> var_graph;
    std::vector<VariablePtr> var_ptrs;
    
    ConstraintGraph(std::vector<VariablePtr>&);
    void add_constraint(int, int);
    int get_num_unassigned_var();
};