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
    board{ board }, solution_board{ board }, voh_ptr{ get_variable_order_heuristic(voh) }, is_forward_checking{ is_forward_checking } {
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

/**
 * @brief When the assignment is complete, fill the board with the assigned values.
 *
 * @param solution_board Filled in baord
 * @param var_ptrs Assignments
 */
void fill_solution_board(std::vector<std::vector<int>>& solution_board, const std::vector<VariablePtr>& var_ptrs) {
    for (auto& var_ptr : var_ptrs) {
        solution_board[var_ptr->row][var_ptr->col] = var_ptr->val;
    }
}

/**
 * @brief Gets the value ordering for a variable. This prefers less constraining values first. Goes through the
 * domain and sorts on the number of reduced domain for the neighboring variables.
 *
 * @param var_ptr Variable whose value ordering to get
 * @return std::vector<int> Value ordering of the domain
 */
std::vector<int> CSPSolver::get_var_val_order(VariablePtr var_ptr) {

}

/**
 * @brief If forward checking is enables, it reduces the domains of neighbors. If no domain gets emptied, inference
 * is successful.
 *
 * @param var_ptr Variable whose assignment needs to be inferred
 * @return true If domain reduction did not empty any domains
 * @return false otherwise
 */
bool CSPSolver::inference(VariablePtr var_ptr) {
    if (this->is_forward_checking) {
        // TODO: do forward checking
        return true;
    } else {
        return true; // no domain reduction, only initial consistency check
    }
}

/**
 * @brief Solves the latin square board
 *
 * @return true if successfull solve, solution in `solution_board` property
 * @return false otherwise
 */
bool CSPSolver::solve() {
    // if complete, fill solution board
    if (is_all_vars_assigned(this->constraint_graph_ptr->var_ptrs)) {
        fill_solution_board(this->solution_board, this->constraint_graph_ptr->var_ptrs);
        return true;
    }

    // get variables according to the heuristic
    auto var_ptr = this->voh_ptr->next_var(); // TODO: needs constraint graph
    // get least constraining value ordering
    for (int val : this->get_var_val_order(var_ptr)) {
        // initial neigbor consistency checking
        if (this->constraint_graph_ptr->is_consistent_assignment(val, var_ptr)) {
            var_ptr->val = val;
            // check if some domain becomes empty after reduction, if not proceed deeper in the branch
            if (this->inference(var_ptr) && this->solve()) {
                return true;
            }
            // if domain became empty of deeper branch failed - try another value
            var_ptr->erase_assignment();
        }
    }
    // no value succeeded, this branch failed
    return false;
}

