#include "../VariableOrderHeuristic.hpp"
#include "../../defs.hpp"

class MaxDegreeHeuristic: VariableOrderHeuristic {
    VariablePtr next_var();
    const std::vector<int> get_unassigned_var_count_for_each_row_col();
};