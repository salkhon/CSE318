#pragma once
#include "../VariableOrderHeuristic.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>

struct RandomHeuristic: VariableOrderHeuristic {
    RandomHeuristic(const ConstraintGraphPtrWk);
    VariablePtr next_var();
};