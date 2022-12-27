#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"

struct MaxDegreeHeuristic: VariableOrderHeuristic {
    MaxDegreeHeuristic(ConstraintGraphPtrWk);
    VariablePtr next_var();
private:
    int degree(VariablePtr);
};