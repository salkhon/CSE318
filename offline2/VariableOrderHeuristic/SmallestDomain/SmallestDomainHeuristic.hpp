#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"

class SmallestDomainHeuristic: VariableOrderHeuristic {
    VariablePtr next_var();
};