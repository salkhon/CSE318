#include "CSP.hpp"

CSP::CSP(int N):
    N{ N }, var_ptrs{ N * N, std::make_shared<Variable>(this) }, constraint_ptrs{ 2 * N, nullptr } {
    // setting up 2N constraints
    for (size_t r = 0; r < N; r++) {
        std::vector<VariablePtr> var_row(N, nullptr);
        for (size_t c = 0; c < N; c++) {
            var_row[c] = this->get_variable(r, c);
        }
        constraint_ptrs[r] = std::make_shared<Constraint>(this, var_row);
    }

    for (size_t c = 0; c < N; c++) {
        std::vector<VariablePtr> var_col(N, nullptr);
        for (size_t r = 0; r < N; r++) {
            var_col[r] = this->get_variable(r, c);
        }
        constraint_ptrs[c + N] = std::make_shared<Constraint>(this, var_col);
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

const std::vector<VariablePtr>& CSP::get_all_var_ptrs() {
    return this->var_ptrs;
}

const std::vector<ConstraintPtr>& CSP::get_all_constraint_ptrs() {
    return this->constraint_ptrs;
}

// /**
//  * @brief A variable has constraints for row and column. The two constraints are in indexes `row` and `N+col`
//  * given variable's index. (Faster implementation than looping over Constraint method)
//  * 
//  * @param row Variable row index
//  * @param col Variable col index
//  * @return int degree of the variable at (row, col)
//  */
// int CSP::get_var_degree(size_t row, size_t col) {
//     int degree = 0;
//     if (!this->get_variable(row, col)->is_assigned()) {
//         for (size_t i = 0; i < this->N; i++) {
//             if (i != col && !this->get_variable(row, i)->is_assigned()) {
//                 degree++;
//             }
//             if (i != row && !this->get_variable(i, col)->is_assigned()) {
//                 degree++;
//             }
//         }
//     }
//     return degree;
// }
