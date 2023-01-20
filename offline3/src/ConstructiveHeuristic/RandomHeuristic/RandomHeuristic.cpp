#include "RandomHeuristic.hpp"

RandomHeuristic::RandomHeuristic(const ConstraintGraphPtrWk con_graph_ptrwk)
    : ConstructiveHeuristic{con_graph_ptrwk} {
}

std::vector<VarPtr> RandomHeuristic::get_var_order() {
    std::vector<VarPtr> ordered_var_ptrs{this->con_graph_ptrwk.lock()->var_ptrs};
    return ordered_var_ptrs;
}
