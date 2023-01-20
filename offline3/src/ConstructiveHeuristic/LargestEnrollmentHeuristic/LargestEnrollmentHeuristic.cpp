#include "LargestEnrollmentHeuristic.hpp"

LargestEnrollmentHeuristic::LargestEnrollmentHeuristic(const std::vector<VarPtr>& var_ptrs)
    : ConstructiveHeuristic{ var_ptrs } {
}

std::vector<VarPtr> LargestEnrollmentHeuristic::get_var_order() {
    return std::vector<VarPtr>();
}
