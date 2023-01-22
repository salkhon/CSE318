#include "LinearPenalty.hpp"

LinearPenalty::LinearPenalty(const ConstraintGraphPtrWk con_graph_ptrwk)
    : Penalty{ con_graph_ptrwk } {
}

float LinearPenalty::apply(int i) {
    return 2 * i;
}