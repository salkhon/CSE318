#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"
#include "../MaxDegree/MaxDegreeHeuristic.hpp"

struct DomainSizeByDegreeHeuristic: public VariableOrderHeuristic {
    DomainSizeByDegreeHeuristic(ConstraintGraphPtrWk);
    VariablePtr next_var();
private:
    double score(VariablePtr);
    int degree(VariablePtr);
};