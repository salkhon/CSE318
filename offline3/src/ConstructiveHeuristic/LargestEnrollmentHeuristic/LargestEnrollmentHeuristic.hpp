#pragma once
#include "definitions.hpp"

struct LargestEnrollmentHeuristic: public ConstructiveHeuristic {
    LargestEnrollmentHeuristic(const std::vector<VarPtr>&);
    std::vector<VarPtr> get_var_order();
};