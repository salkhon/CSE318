#include "CSPSolver.hpp"
#include <algorithm>
#include "../VariableOrderHeuristic/VariableOrderHeuristic.hpp"
#include "../VariableOrderHeuristic/SmallestDomain/SmallestDomainHeuristic.hpp"
#include "../VariableOrderHeuristic/SmallestDomainMaxDegree/SmallestDomainMaxDegreeHeuristic.hpp"
#include "../VariableOrderHeuristic/Random/RandomHeuristic.hpp"
#include "../VariableOrderHeuristic/MaxDegree/MaxDegreeHeuristic.hpp"
#include "../VariableOrderHeuristic/DomainSizeByDegree/DomainSizeByDegreeHeuristic.hpp"
#include <iostream>

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

    std::vector<bool> is_row_domains(board.size(), true), is_col_domains(board.size(), true); // idx i represents domain i+1

    for (size_t i = 0; i < board.size(); i++) {
        for (size_t j = 0; j < board.size(); j++) {
            // cross out domains for row i
            if (board[i][j] != 0) {
                is_row_domains[board[i][j] - 1] = false;
            }

            // cross out domains for col i
            if (board[j][i] != 0) {
                is_col_domains[board[j][i] - 1] = false;
            }
        }

        for (size_t k = 0; k < board.size(); k++) {
            // if domain was not crossed out, add it to the list
            if (is_row_domains[k]) {
                row_doms[i].push_back(k + 1);
            }

            if (is_col_domains[k]) {
                col_doms[i].push_back(k + 1);
            }
        }
        // for computing set difference
        std::sort(row_doms[i].begin(), row_doms[i].end());
        std::sort(col_doms[i].begin(), col_doms[i].end());

        // erase crosses
        std::fill(is_row_domains.begin(), is_row_domains.end(), true);
        std::fill(is_col_domains.begin(), is_col_domains.end(), true);
    }

    return std::make_pair(row_doms, col_doms);
}

void print_vector(const std::vector<int>& vec) {
    std::cout << "[ ";
    for (int val : vec) {
        std::cout << val << ", ";
    }
    std::cout << "]";
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

VOHPtr get_variable_order_heuristic(const int voh, const ConstraintGraphPtr constraint_graph_ptr) {
    if (voh == SMALLEST_DOMAIN) {
        return std::make_shared<SmallestDomainHeuristic>(constraint_graph_ptr);
    } else if (voh == MAX_DEGREE) {
        return std::make_shared<MaxDegreeHeuristic>(constraint_graph_ptr);
    } else if (voh == SMALLEST_DOM_WITH_MAX_DEGREE) {
        return std::make_shared<SmallestDomainMaxDegreeHeuristic>(constraint_graph_ptr);
    } else if (voh == DOM_DEGREE_RATIO) {
        return std::make_shared<DomainSizeByDegreeHeuristic>(constraint_graph_ptr);
    } else if (voh == RANDOM) {
        return std::make_shared<RandomHeuristic>(constraint_graph_ptr);
    } else {
        return nullptr;
    }
}

/**
 * @brief Construct a new CSPSolver::CSPSolver object from the provided board. Only the `0` values will be
 * variables, and constraints need to be setup consisting of those variables.
 *
 * @param board The Latin Square Board, with `0` indicating variables.
 */
CSPSolver::CSPSolver(std::vector<std::vector<int>> board, int voh, bool is_forward_checking):
    board{ board }, solution_board{ board }, constraint_graph_ptr{ get_constraint_graph(board) },
    voh_ptr{ get_variable_order_heuristic(voh, constraint_graph_ptr) }, is_forward_checking{ is_forward_checking },
    num_nodes{ 0 }, num_backtrack{ 0 } {
    // std::cout << *this->constraint_graph_ptr << std::endl;
    // std::cout << "VOH=" << voh << "\t\t" << "forwardchecking=" << is_forward_checking << std::endl;
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
        }) == var_ptrs.end(); // no unassigned vars
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
    std::vector<int> val_order{ var_ptr->domain };
    std::vector<int> val_overlap_count(this->board.size(), 0);

    // count the occurrence of each possible value in var_ptr neighbor variable domains
    for (int nbr_id : this->constraint_graph_ptr->var_graph[var_ptr->id]) {
        for (int dom_val : this->constraint_graph_ptr->var_ptrs[nbr_id]->domain) {
            val_overlap_count[dom_val - 1]++;
        }
    }

    std::sort(val_order.begin(), val_order.end(),
        [&val_overlap_count](int val1, int val2) {
            return val_overlap_count[val1 - 1] < val_overlap_count[val2 - 1];
        }
    );
    return val_order;
}

/**
 * @brief Remove the assigned value from the domain of neighboring unassigned variables.
 *
 * @param val Assigned value
 * @param neighbor_vars Constraint neighbors of the assigned variable
 * @param var_ptrs Variable id to object mapping
 * @return std::vector<int> List of variable id's whose domain was reduced by assigned value
 */
std::vector<int> reduce_domain(int val, const std::vector<int>& neighbor_vars, const std::vector<VariablePtr>& var_ptrs) {
    std::vector<int> reduced_vars;

    for (auto neighbord_id : neighbor_vars) {
        if (var_ptrs[neighbord_id]->is_assigned()) {
            continue;
        }
        // reduce domain only for unassigned variables
        auto& neighbor_domain = var_ptrs[neighbord_id]->domain;
        auto val_pos_iter = std::find(neighbor_domain.begin(), neighbor_domain.end(), val);
        if (val_pos_iter != neighbor_domain.end()) {
            // val found in neighbor domain
            neighbor_domain.erase(val_pos_iter);
            reduced_vars.push_back(neighbord_id);
        }
    }

    return reduced_vars;
}

/**
 * @brief If forward checking is enabled, it reduces the domains of neighbors. If no domain gets emptied, inference
 * is successful.
 *
 * @param var_ptr Variable whose assignment needs to be inferred
 * @return true If domain reduction did not empty any domains
 * @return false otherwise
 */
std::pair<bool, std::vector<int>> CSPSolver::inference(VariablePtr var_ptr) {
    if (this->is_forward_checking) {
        auto reduced_vars = reduce_domain(var_ptr->val,
            this->constraint_graph_ptr->var_graph[var_ptr->id],
            this->constraint_graph_ptr->var_ptrs);

        return std::make_pair(
            std::find_if(
                reduced_vars.begin(), reduced_vars.end(),
                [this](int var_id) {
                    return this->constraint_graph_ptr->var_ptrs[var_id]->domain.empty();
                }
            ) == reduced_vars.end(), // no empty domain list was found among the reduced_vars
                    reduced_vars
                    );
    } else {
        return std::make_pair(true, std::vector<int>{}); // no domain reduction, only initial consistency check
    }
}

/**
 * @brief Add back the domain reduced in forward checking as a part of backtracking.
 *
 * @param val Assigned value to be restored
 * @param reduced_vars Variables (id) which were reduced during forward checking
 */
void CSPSolver::undo_inference(int val, const std::vector<int>& reduced_vars) {
    if (this->is_forward_checking) {
        for (auto var_id : reduced_vars) {
            this->constraint_graph_ptr->var_ptrs[var_id]->domain.push_back(val);
        }
    }
}

/**
 * @brief Recursive CSP Solver.
 *
 * @param n_var_assigned Number of variables assigned so far
 * @return true If assignment on this branch is successful
 * @return false otherwise
 */
bool CSPSolver::solve_helper(int n_var_assigned) {
    // if complete, fill solution board
    if (n_var_assigned == this->constraint_graph_ptr->var_ptrs.size()) {
        fill_solution_board(this->solution_board, this->constraint_graph_ptr->var_ptrs);
        return true;
    }
    
    this->num_nodes++;

    // if no recursive call is made, this is a leaf node
    bool any_branch_taken = false;

    // get variables according to the heuristic
    auto var_ptr = this->voh_ptr->next_var();

    // get least constraining value ordering
    for (int val : this->get_var_val_order(var_ptr)) {
        // initial neighbor consistency checking
        if (this->constraint_graph_ptr->is_consistent_assignment(val, var_ptr)) {
            var_ptr->val = val;

            // check if some domain becomes empty after reduction, if not proceed deeper in the branch
            auto [is_success, reduced_vars] = this->inference(var_ptr);
            if (is_success) {
                any_branch_taken = true;
                if (this->solve_helper(n_var_assigned + 1)) {
                    return true;
                }
            }

            // undo domain reduction
            this->undo_inference(val, reduced_vars);

            // if domain became empty or deeper branch failed - try another value
            var_ptr->erase_assignment();
        }
    }

    if (!any_branch_taken) {
        // leaf node
        this->num_backtrack++;
    }

    // no value succeeded, this branch failed
    return false;
}

/**
 * @brief Solves the latin square board
 *
 * @return true if successfull solve, solution in `solution_board` property
 * @return false otherwise
 */
bool CSPSolver::solve() {
    return this->solve_helper(0);
}

