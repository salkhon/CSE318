#pragma once
#include <vector>
#include <memory>
#include <algorithm>

#include "../../Variable/Variable.hpp"
#include "../../ConstraintGraph/ConstraintGraph.hpp"
#include "../ConstructiveHeuristic.hpp"

struct LargestDegreeHeuristic: public ConstructiveHeuristic {
    LargestDegreeHeuristic(const ConstraintGraphPtrWk);
    std::vector<VarPtr> get_var_order();
};

using DegreeHeuPtr = std::shared_ptr<LargestDegreeHeuristic>;