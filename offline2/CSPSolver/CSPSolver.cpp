#include "CSPSolver.hpp"
#include <algorithm>
#include <utility>
#include "../VariableOrderHeuristic/VariableOrderHeuristic.hpp"
#include "../VariableOrderHeuristic/SmallestDomain/SmallestDomainHeuristic.hpp"
#include "../VariableOrderHeuristic/SmallestDomainMaxDegree/SmallestDomainMaxDegreeHeuristic.hpp"
#include "../VariableOrderHeuristic/Random/RandomHeuristic.hpp"
#include "../VariableOrderHeuristic/MaxDegree/MaxDegreeHeuristic.hpp"
#include "../VariableOrderHeuristic/DomainSizeByDegree/DomainSizeByDegreeHeuristic.hpp"

/**
 * @brief Construct a new CSPSolver::CSPSolver object from the provided board. Only the `0` values will be
 * variables, and constraints need to be setup consisting of those variables.
 *
 * @param board The Latin Square Board, with `0` indicating variables.
 */
CSPSolver::CSPSolver(std::vector<std::vector<int>> board, int voh, bool is_forward_checking = true):
    board{ board }, voh_ptr{ get_variable_order_heuristic(voh) }, is_forward_checking{ is_forward_checking } {
}

/**
 * @brief Create domain lists for each row and column by iterating through board row and column.
 *
 * @param board Board
 * @return std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> Pair of mappings for each row and
 * col list
 */
std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>>
get_row_col_dom(const std::vector<std::vector<int>>& board) {
    std::vector<std::vector<int>> row_doms(board.size(), std::vector<int>{});
    std::vector<std::vector<int>> col_doms(board.size(), std::vector<int>{});

    std::vector<bool> row_domain(board.size(), true), col_domain(board.size(), true); // idx i represents domain i+1

    for (size_t i = 0; i < board.size(); i++) {
        for (size_t j = 0; j < board.size(); j++) {
            // cross out domains for row i
            if (board[i][j] != 0) {
                row_domain[board[i][j]] = false;
            }

            // cross out domains for col i
            if (board[j][i] != 0) {
                col_domain[board[j][i]] = false;
            }
        }

        for (size_t k = 0; k < board.size(); k++) {
            // if domain was not crossed out, add it to the list
            if (row_domain[k]) {
                row_doms[k].push_back(k + 1);
            }

            if (col_domain[k]) {
                col_doms[k].push_back(k + 1);
            }
        }
        // for computing set difference
        std::sort(row_doms[i].begin(), row_doms[i].end());
        std::sort(col_doms[i].begin(), col_doms[i].end());

        std::fill(row_domain.begin(), row_domain.end(), false);
        std::fill(col_domain.begin(), col_domain.end(), false);
    }

    return std::make_pair(row_doms, col_doms);
}

/**
 * @brief Construct a constraint graph from the board.
 *
 * @param board Board
 * @return ConstraintGraphPtr Constraint graph
 */
ConstraintGraphPtr get_constraint_graph(const std::vector<std::vector<int>>& board) {
    std::vector<VariablePtr> var_ptrs;
    int var_id = 0;
    auto [row_doms, col_doms] = get_row_col_dom(board);

    for (size_t row = 0; row < board.size(); row++) {
        for (size_t col = 0; col < board.size(); col++) {
            if (board[row][col] == 0) {
                std::vector<int> row_col_intersection;
                std::set_intersection(row_doms[row].begin(), row_doms[row].end(),
                    col_doms[col].begin(), col_doms[col].end(), std::back_inserter(row_col_intersection));

                var_ptrs.push_back(std::make_shared<Variable>(var_id++, row, col, row_col_intersection));
            }
        }
    }

    return std::make_shared<ConstraintGraph>(var_ptrs);
}

VOHPtr get_variable_order_heuristic(int voh) {
    if (voh == 1) {
        return std::make_shared<SmallestDomainHeuristic>();
    } else if (voh == 2) {
        return std::make_shared<MaxDegreeHeuristic>();
    } else if (voh == 3) {
        return std::make_shared<SmallestDomainMaxDegreeHeuristic>();
    } else if (voh == 4) {
        return std::make_shared<DomainSizeByDegreeHeuristic>();
    } else if (voh == 5) {
        return std::make_shared<RandomHeuristic>();
    } else {
        return nullptr;
    }
}

/**
 * @brief Checks if all the variables are assigned.
 *
 * @param var_ptrs Variables
 * @return true if all variables have a value
 * @return false otherwise
 */
bool is_all_vars_assigned(const std::vector<VariablePtr>& var_ptrs) {
    return std::find_if(var_ptrs.begin(), var_ptrs.end(), [](VariablePtr var_ptr) {
        return !var_ptr->is_assigned();
        }) == var_ptrs.end();
}

void CSPSolver::solve() {
    if (is_all_vars_assigned(this->constraint_graph_ptr->var_ptrs)) {
        
    }
}