#pragma once
#include <vector>
#include <memory>
#include <algorithm>

#include "../ConstructiveHeuristic.hpp"
#include "../../ConstraintGraph/ConstraintGraph.hpp"
#include "../../Variable/Variable.hpp"

struct RandomHeuristic: public ConstructiveHeuristic {
    RandomHeuristic(const ConstraintGraphPtrWk);

    void assign_variables_in_order();
};

using RandHeuPtr = std::shared_ptr<RandomHeuristic>;