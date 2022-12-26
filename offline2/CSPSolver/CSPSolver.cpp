#include "CSPSolver.hpp"
#include <algorithm>
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
 * @brief Create domain lists for each row by iterating through the board rows. 
 * 
 * @param board Board
 * @return std::vector<std::vector<int>> Mapping for each row domain list
 */
std::vector<std::vector<int>> get_row_dom(const std::vector<std::vector<int>>& board) {
    std::vector<bool> domain(board.size(), true); // idx i represents domain i+1
    std::vector<std::vector<int>> row_doms(board.size(), std::vector<int>{});

    for (size_t row = 0; row < board.size(); row++) {
        for (size_t col = 0; col < board.size(); col++) {
            if (board[row][col] != 0) {
                domain[board[row][col]] = false;
            }
        }

        for (size_t i = 0; i < board.size(); i++) {
            if (domain[i]) {
                row_doms[row].push_back(i + 1);
            }
        }
        std::sort(row_doms[row].begin(), row_doms[row].end());

        std::fill(domain.begin(), domain.end(), false);
    }

    return row_doms;
}

/**
 * @brief Create domain lists for each column by iterating through the board columns. 
 * 
 * @param board Board
 * @return std::vector<std::vector<int>> Mapping for each col domain list
 */
std::vector<std::vector<int>> get_col_dom(const std::vector<std::vector<int>>& board) {
    std::vector<bool> domain(board.size(), true); // idx i represents domain i+1
    std::vector<std::vector<int>> col_doms(board.size(), std::vector<int>{});

    for (size_t col = 0; col < board.size(); col++) {
        for (size_t row = 0; row < board.size(); row++) {
            if (board[row][col] != 0) {
                domain[board[row][col]] = false;
            }
        }

        for (size_t i = 0; i < board.size(); i++) {
            if (domain[i]) {
                col_doms[col].push_back(i + 1);
            }
        }
        std::sort(col_doms[col].begin(), col_doms[col].end());

        std::fill(domain.begin(), domain.end(), false);
    }

    return col_doms;
}

ConstraintGraphPtr get_constraint_graph(const std::vector<std::vector<int>>& board) {
    std::vector<VariablePtr> var_ptrs;
    int var_id = 0;
    auto row_doms = get_row_dom(board);
    auto col_doms = get_col_dom(board);

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

    ConstraintGraphPtr constraint_graph_ptr = std::make_shared<ConstraintGraph>(var_id);
    /**
     * @brief Go through the board
     * Each row and column start with domain N, then deduct non zero values, each variable on that row or col
     * gets that deducted domain.
     *
     */
    std::vector<bool> domain(board.size(), true);
    int var_id = 0;
    for (size_t row = 0; row < board.size(); row++) {
        for (size_t col = 0; col < board.size(); col++) {
            if (board[row][col] != 0) {
                domain[board[row][col]] = false;
            } else {
                constraint_graph_ptr->var_ptrs[var_id]->row = row;
                constraint_graph_ptr->var_ptrs[var_id]->col = col;
                var_id++;
            }
        }
    }
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

void CSPSolver::solve() {

}