#pragma once
#include "../VariableOrderHeuristic.hpp"
#include <algorithm>

struct SmallestDomainMaxDegreeHeuristic: VariableOrderHeuristic {
    SmallestDomainMaxDegreeHeuristic(const ConstraintGraphPtrWk);
    VariablePtr next_var();
};