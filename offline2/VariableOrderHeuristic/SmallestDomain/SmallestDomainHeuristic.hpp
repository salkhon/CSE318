#pragma once
#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"
#include <algorithm>

struct SmallestDomainHeuristic: VariableOrderHeuristic {
    SmallestDomainHeuristic(ConstraintGraphPtrWk);
    VariablePtr next_var();
};