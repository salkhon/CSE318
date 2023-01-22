#include "ExponentialPenalty.hpp"

ExponentialPenalty::ExponentialPenalty(const ConstraintGraphPtrWk con_graph_ptrwk)
    : Penalty{ con_graph_ptrwk } {
}

float ExponentialPenalty::apply(int i) {
    return i > 0 ? std::pow(2, i) : 0;
}
