#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"

struct RandomHeuristic: VariableOrderHeuristic {
    RandomHeuristic(CSPPtrWk);
    VariablePtr next_var();
};