#include "SaturationDegreeHeuristic.hpp"

SaturationDegreeHeuristic::SaturationDegreeHeuristic(const std::vector<VarPtr>& var_ptrs)
    : ConstructiveHeuristic{ var_ptrs } {
}

std::vector<VarPtr> SaturationDegreeHeuristic::get_var_order() {
    return std::vector<VarPtr>();
}
