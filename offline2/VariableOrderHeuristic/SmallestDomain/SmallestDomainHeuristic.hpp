#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"

struct SmallestDomainHeuristic: VariableOrderHeuristic {
    SmallestDomainHeuristic(CSPPtrWk);
    VariablePtr next_var();
};