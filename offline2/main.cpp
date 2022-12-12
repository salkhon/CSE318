#include <iostream>
#include "CSP/CSP.hpp"
#include "CSPSolver/CSPSolver.hpp"

int main() {
    Variable variable{ {3, 4, 5} };
    Constraint constraint;
    VariableOrderHeuristic voh;
    CSP csp;
    CSPSolver csp_solver;
    return 0;
}