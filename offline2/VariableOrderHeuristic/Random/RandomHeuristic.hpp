#pragma once
#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>

struct RandomHeuristic: VariableOrderHeuristic {
    RandomHeuristic(ConstraintGraphPtrWk);
    VariablePtr next_var();
};