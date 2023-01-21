#include "LinearPenalty.hpp"

LinearPenalty::LinearPenalty(const ConstraintGraphPtrWk con_graph_ptrwk)
    : Penalty{ con_graph_ptrwk } {
}

double LinearPenalty::get_penalty() {
    auto con_graph_ptr = this->con_graph_ptrwk.lock();
    return 0.0;
}
