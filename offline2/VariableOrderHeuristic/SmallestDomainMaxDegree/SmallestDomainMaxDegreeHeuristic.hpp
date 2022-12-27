#pragma once
#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"
#include "../MaxDegree/MaxDegreeHeuristic.hpp"
#include <algorithm>

struct SmallestDomainMaxDegreeHeuristic: VariableOrderHeuristic {
    SmallestDomainMaxDegreeHeuristic(ConstraintGraphPtrWk);
    VariablePtr next_var();
private:
    int degree(VariablePtr);
};