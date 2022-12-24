#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"

struct RandomHeuristic: VariableOrderHeuristic {
    RandomHeuristic(CSPPtr);
    VariablePtr next_var();
};