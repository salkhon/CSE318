#include "PairSwap.hpp"

PairSwap::PairSwap(const ConstraintGraphPtrWk constraint_graph_ptrwk)
    : constraint_graph_ptrwk{ constraint_graph_ptrwk } {
}

std::pair<int, int> PairSwap::get_pair() {
    return std::pair<int, int>();
}
