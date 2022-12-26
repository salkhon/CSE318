#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"
#include "../MaxDegree/MaxDegreeHeuristic.hpp"

struct SmallestDomainMaxDegreeHeuristic: VariableOrderHeuristic {
    SmallestDomainMaxDegreeHeuristic(CSPPtrWk csp_ptrwk);
    VariablePtr next_var();
private:
    MaxDegreeHeuristic max_degree_heuristic;
};