#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"

class RandomHeuristic: VariableOrderHeuristic {
    RandomHeuristic(CSPPtr);
    VariablePtr next_var();
};