#pragma once
#include "../VariableOrderHeuristic.hpp"
#include <algorithm>

struct SmallestDomainHeuristic: VariableOrderHeuristic {
    SmallestDomainHeuristic(const ConstraintGraphPtrWk);
    VariablePtr next_var();
};