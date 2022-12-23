#include "CSP.hpp"

CSP::CSP(int N):
    N{ N }, var_ptrs{ N * N, std::make_shared<Variable>(this) }, constraint_ptrs{ 2 * N, nullptr } {
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

VariablePtr CSP::get_variable(size_t row, size_t col) {
    return this->var_ptrs[row * this->N + col];
}