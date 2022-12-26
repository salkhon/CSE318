#include "ConstraintGraph.hpp"
#include <algorithm>

/**
 * @brief Construct the constraint graph from the variables considering their row col positions.
 *
 * @param var_ptrs Variables for th graph
 * @return std::vector<std::vector<int>> Adjacency list for constraint graph
 */
std::vector<std::vector<int>> get_constraint_graph(const std::vector<VariablePtr>& var_ptrs) {
    std::vector<std::vector<int>> constraint_graph(var_ptrs.size(), std::vector<int>{});

    for (size_t i = 0; i < var_ptrs.size(); i++) {
        for (size_t j = i + 1; j < var_ptrs.size(); j++) {
            if (var_ptrs[i]->row == var_ptrs[j]->row) {
                constraint_graph[i].push_back(j);
                constraint_graph[j].push_back(i);
            }
        }
    }

    return constraint_graph;
}

/**
 * @brief Construct a new Constraint Graph:: Constraint Graph object
 *
 * @param num_var Number of variables
 */
ConstraintGraph::ConstraintGraph(std::vector<VariablePtr>& var_ptrs):
    var_ptrs{ var_ptrs }, var_graph{ get_constraint_graph(var_ptrs) } {
}

/**
 * @brief Adds uniqueness constraint between variables if none exists.
 *
 * @param v1 Variable 1
 * @param v2 Variable 2
 */
void ConstraintGraph::add_constraint(int v1, int v2) {
    if (std::find(this->var_graph[v1].begin(), this->var_graph[v1].end(), v2) == this->var_graph[v1].end()) {
        this->var_graph[v1].push_back(v2);
        this->var_graph[v2].push_back(v1);
    }
}

int ConstraintGraph::get_num_unassigned_var() {
    return std::count_if(this->var_ptrs.begin(), this->var_ptrs.end(), [](VariablePtr var_ptr) {
        return !var_ptr->is_assigned();
        });
}
