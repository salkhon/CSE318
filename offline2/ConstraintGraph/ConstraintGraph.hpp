#pragma once
#include "../Variable/Variable.hpp"
#include <vector>
#include <memory>
#include <algorithm>

/**
 * @brief Container for the variables and the uniqueness constraint graph between them.
 */
struct ConstraintGraph {
    std::vector<std::vector<int>> var_graph;
    std::vector<VariablePtr> var_ptrs;
    
    ConstraintGraph(std::vector<VariablePtr>&);
    void add_constraint(int, int);
    int get_num_unassigned_var();
    bool is_consistent_assignment(int value, VariablePtr var_ptr);
    friend std::ostream& operator<< (std::ostream& ostrm, const ConstraintGraph& var);
};

using ConstraintGraphPtr = std::shared_ptr<ConstraintGraph>;
using ConstraintGraphPtrWk = std::weak_ptr<ConstraintGraph>;
