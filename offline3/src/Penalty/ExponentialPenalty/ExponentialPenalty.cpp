#include "ExponentialPenalty.hpp"

ExponentialPenalty::ExponentialPenalty(const ConstraintGraphPtrWk con_graph_ptrwk)
    : Penalty{ con_graph_ptrwk } {
}

double ExponentialPenalty::get_penalty() {
    return 0.0;
}
