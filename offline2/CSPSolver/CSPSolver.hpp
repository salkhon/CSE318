#pragma once
#include <vector>
#include <memory>
#include <utility>
#include "../Variable/Variable.hpp"
#include "../ConstraintGraph/ConstraintGraph.hpp"
#include "../VariableOrderHeuristic/VariableOrderHeuristic.hpp"

/**
 * @brief Initialize a CSP based on N, and solve it.
 */
struct CSPSolver {
    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> solution_board;
    ConstraintGraphPtr constraint_graph_ptr;
    VOHPtr voh_ptr;
    bool is_forward_checking;
    unsigned long long num_nodes, num_backtrack;

    CSPSolver(std::vector<std::vector<int>>, int, bool = true);
    bool solve();
private:
    bool solve_helper(int);
    std::vector<int> get_var_val_order(VariablePtr);
    std::pair<bool, std::vector<int>> inference(VariablePtr);
    void undo_inference(int, const std::vector<int>&);
};

enum VOH {
    SMALLEST_DOMAIN = 1, MAX_DEGREE, SMALLEST_DOM_WITH_MAX_DEGREE, DOM_DEGREE_RATIO, RANDOM
};

using CSPSolverPtr = std::shared_ptr<CSPSolver>;