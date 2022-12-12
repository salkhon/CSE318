#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "../VariableOrderHeuristic/VariableOrderHeuristic.hpp"
#include "../CSP/CSP.hpp"

using VariableOrderHeuristicPtr = std::shared_ptr<VariableOrderHeuristic>;
using CSPPtr = std::shared_ptr<CSP>;

struct CSPSolver {
    VariableOrderHeuristicPtr voh_ptr;
    CSPPtr csp_ptr;
    std::unordered_map<VariablePtr, int> assignments;

    void solve();
    int next_val(const VariablePtr);
};