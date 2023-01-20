#pragma once
#include <vector>
#include <memory>
#include <algorithm>

#include "../../Variable/Variable.hpp"
#include "../../ConstraintGraph/ConstraintGraph.hpp"
#include "../ConstructiveHeuristic.hpp"

struct LargestEnrollmentHeuristic: public ConstructiveHeuristic {
    LargestEnrollmentHeuristic(const ConstraintGraphPtrWk);
    std::vector<VarPtr> get_var_order();
};

using EnrollHeuPtr = std::shared_ptr<LargestEnrollmentHeuristic>;