#pragma once
#include <vector>
#include <memory>
#include <algorithm>

#include "../../Variable/Variable.hpp"
#include "../../ConstraintGraph/ConstraintGraph.hpp"
#include "../ConstructiveHeuristic.hpp"

struct SaturationDegreeHeuristic: public ConstructiveHeuristic {
    SaturationDegreeHeuristic(const ConstraintGraphPtrWk);
    std::vector<VarPtr> get_var_order();
};

using SatHeuPtr = std::shared_ptr<SaturationDegreeHeuristic>;