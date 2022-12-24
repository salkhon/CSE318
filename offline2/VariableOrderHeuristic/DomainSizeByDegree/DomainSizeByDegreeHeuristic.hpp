#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"
#include "../MaxDegree/MaxDegreeHeuristic.hpp"

struct DomainSizeByDegreeHeuristic: public VariableOrderHeuristic {
    DomainSizeByDegreeHeuristic(CSPPtr);
    VariablePtr next_var();
private:
    MaxDegreeHeuristic max_degree_heuristic;
};