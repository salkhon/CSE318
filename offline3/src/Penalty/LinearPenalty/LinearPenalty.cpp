#include "LinearPenalty.hpp"

LinearPenalty::LinearPenalty(const ConstraintGraphPtrWk con_graph_ptrwk)
    : Penalty{ con_graph_ptrwk } {
}

float LinearPenalty::get_penalty() {
    return this->get_sum_of_gap_between_neighbors() * 2;
}
