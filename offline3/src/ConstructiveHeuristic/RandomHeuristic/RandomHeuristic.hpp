#pragma once
#include <vector>
#include <memory>
#include <algorithm>

#include "../ConstructiveHeuristic.hpp"
#include "../../ConstraintGraph/ConstraintGraph.hpp"
#include "../../Variable/Variable.hpp"

struct RandomHeuristic: public ConstructiveHeuristic {
    RandomHeuristic(const ConstraintGraphPtrWk);

    std::vector<VarPtr> get_var_order();
};

using RandHeuPtr = std::shared_ptr<RandomHeuristic>;