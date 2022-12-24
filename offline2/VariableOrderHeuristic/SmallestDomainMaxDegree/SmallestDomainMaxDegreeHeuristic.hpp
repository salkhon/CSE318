#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"
#include "../MaxDegree/MaxDegreeHeuristic.hpp"

struct SmallestDomainMaxDegreeHeuristic: VariableOrderHeuristic {
    SmallestDomainMaxDegreeHeuristic(CSPPtr csp_ptr);
    VariablePtr next_var();
private:
    MaxDegreeHeuristic max_degree_heuristic;
};