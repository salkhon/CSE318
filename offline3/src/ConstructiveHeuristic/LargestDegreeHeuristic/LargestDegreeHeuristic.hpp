#pragma once
#include "definitions.hpp"

struct LargestDegreeHeuristic: public ConstructiveHeuristic {
    LargestDegreeHeuristic(const ConstraintGraphPtrWk);
    std::vector<VarPtr> get_var_order();
};