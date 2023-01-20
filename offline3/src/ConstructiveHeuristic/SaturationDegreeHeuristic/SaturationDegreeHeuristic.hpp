#pragma once
#include "definitions.hpp"

struct SaturationDegreeHeuristic: public ConstructiveHeuristic {
    SaturationDegreeHeuristic(const std::vector<VarPtr>&);
    std::vector<VarPtr> get_var_order();
};