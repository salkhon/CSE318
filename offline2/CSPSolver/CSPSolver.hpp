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

    CSPSolver(std::vector<std::vector<int>>, int, bool = true);
    bool solve();
private:
    std::vector<int> get_var_val_order(VariablePtr);
    std::pair<bool, std::vector<int>> inference(VariablePtr);
    void undo_inference(int, const std::vector<int>&);
};

using CSPSolverPtr = std::shared_ptr<CSPSolver>;