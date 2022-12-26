#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"

struct MaxDegreeHeuristic: VariableOrderHeuristic {
    MaxDegreeHeuristic(CSPPtrWk);
    VariablePtr next_var();
    const std::vector<int> get_unassigned_var_count_for_each_row_col();
};