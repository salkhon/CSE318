#include "ExponentialPenalty.hpp"

ExponentialPenalty::ExponentialPenalty(const ConstraintGraphPtrWk con_graph_ptrwk)
    : Penalty{ con_graph_ptrwk } {
}

float ExponentialPenalty::get_penalty() {
    return std::pow(2, this->get_sum_of_gap_between_neighbors());
}
