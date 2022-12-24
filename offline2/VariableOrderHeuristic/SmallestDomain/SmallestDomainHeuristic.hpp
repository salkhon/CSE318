#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"

struct SmallestDomainHeuristic: VariableOrderHeuristic {
    VariablePtr next_var();
};