#pragma once
#include "../VariableOrderHeuristic.hpp"

struct MaxDegreeHeuristic: VariableOrderHeuristic {
    MaxDegreeHeuristic(const ConstraintGraphPtrWk);
    VariablePtr next_var();
};
