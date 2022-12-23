#pragma once
#include "../defs.hpp"
#include <vector>
#include <memory>
#include <unordered_map>
#include "../VariableOrderHeuristic/VariableOrderHeuristic.hpp"
#include "../CSP/CSP.hpp"

/**
 * @brief Initialize a CSP based on N, and solve it. 
 */
struct CSPSolver {
    VOHPtr voh_ptr;
    CSPPtr csp_ptr;
    std::unordered_map<VariablePtr, int> assignments;

    void solve();
    int next_val(const VariablePtr);
};