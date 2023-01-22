#include "ConstructiveHeuristic.hpp"

ConstructiveHeuristic::ConstructiveHeuristic(const ConstraintGraphPtrWk constraint_graph_ptrwk)
    : constraint_graph_ptrwk{ constraint_graph_ptrwk },
    days_assigned(constraint_graph_ptrwk.lock()->var_ptrs.size(), false) {
}

int ConstructiveHeuristic::get_lowest_assignagble_day(VarPtr var_ptr) {
    auto constraint_graph_ptr = this->constraint_graph_ptrwk.lock();

    for (auto neighbor_id : constraint_graph_ptr->adj_list[var_ptr->id]) {
        if (!constraint_graph_ptr->var_ptrs[neighbor_id]->is_day_assigned()) {
            continue;
        }

        days_assigned[constraint_graph_ptr->var_ptrs[neighbor_id]->day] = true;
    }

    // find lowest unmarked day
    int lowest_day = 0;
    while (days_assigned[lowest_day]) {
        lowest_day++;
    }

    std::fill(days_assigned.begin(), days_assigned.end(), false);
    return lowest_day;
}
