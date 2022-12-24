#include "CSP.hpp"
#include <numeric>

CSP::CSP(std::vector<std::vector<int>>& board): N{ board.size() }, var_ptrs{ N * N, nullptr } {
    // given the values for the row and col, we can minimize the domain of each variable
    for (size_t i = 0; i < this->N; i++) {
        for (size_t j = 0; j < this->N; j++) {
            if (board[i][j] == 0) {
                // variable
                std::vector<int> domain(this->N);
                std::iota(domain.begin(), domain.end(), 1);
                for (size_t k = 0; k < this->N; k++) {
                    domain.erase(std::find(domain.begin(), domain.end(), board[i][k]));
                    domain.erase(std::find(domain.begin(), domain.end(), board[k][j]));
                }
                this->set_variable(i, j, std::make_shared<Variable>(domain, this));
            }
        }
    }

    // create constraints for non null variables in the board
    for (size_t i = 0; i < this->N; i++) {
        // create constraint for row i and col i
        std::vector<VariablePtr> row_var_ptrs;
        std::vector<VariablePtr> col_var_ptrs;
        for (size_t j = 0; j < this->N; j++) {
            // accumulating other variables for row i and col i
            if (this->get_variable(i, j)) {
                row_var_ptrs.push_back(this->get_variable(i, j));
            }
            if (this->get_variable(j, i)) {
                col_var_ptrs.push_back(this->get_variable(j, i));
            }
        }
        this->constraint_ptrs.push_back(std::make_shared<Constraint>(row_var_ptrs, this));
        this->constraint_ptrs.push_back(std::make_shared<Constraint>(col_var_ptrs, this));
    }
}

/**
 * @brief Getter for board variables according to row and column.
 *
 * @param row Board row
 * @param col Board column
 * @return VariablePtr Pointer to the variable of the board on (row, col)
 */
VariablePtr CSP::get_variable(size_t row, size_t col) {
    return this->var_ptrs[row * this->N + col];
}

void CSP::set_variable(size_t row, size_t col, VariablePtr var_ptr) {
    this->var_ptrs[row * this->N + col] = var_ptr;
}

const std::vector<VariablePtr>& CSP::get_all_var_ptrs() {
    return this->var_ptrs;
}

const std::vector<ConstraintPtr>& CSP::get_all_constraint_ptrs() {
    return this->constraint_ptrs;
}
