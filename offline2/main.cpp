#include <iostream>
#include "CSPSolver/CSPSolver.hpp"
#include <vector>
#include <memory>

int main() {
    std::vector<std::vector<int>> board = {
        {1, 2, 0},
        {0, 0, 1},
        {3, 0, 2}
    };

    CSPSolver csp_solver(board, 1);

    return 0;
}