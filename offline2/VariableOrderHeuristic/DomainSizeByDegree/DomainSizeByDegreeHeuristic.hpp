#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"

struct DomainSizeByDegreeHeuristic: public VariableOrderHeuristic {
    VariablePtr next_var();
};