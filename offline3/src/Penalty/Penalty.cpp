#include "Penalty.hpp"

Penalty::Penalty(const ConstraintGraphPtrWk con_graph_ptrwk)
    : con_graph_ptrwk{ con_graph_ptrwk } {
}

float Penalty::calc_pen() {
    auto con_graph_ptr = this->con_graph_ptrwk.lock();
    float penalty = 0;
    int day1, day2, n;

    for (size_t var_id = 0; var_id < con_graph_ptr->var_ptrs.size(); var_id++) {
        if (!con_graph_ptr->var_ptrs[var_id]->is_day_assigned()) {
            continue;
        }

        day1 = con_graph_ptr->var_ptrs[var_id]->day;

        for (auto neighbor_id : con_graph_ptr->adj_list[var_id]) {
            if (!con_graph_ptr->var_ptrs[neighbor_id]->is_day_assigned()) {
                continue;
            }

            day2 = con_graph_ptr->var_ptrs[neighbor_id]->day;
            
            n = std::max(0, 5 - std::abs(day1 - day2));
            n = n > 0 ? this->apply(n) : 0;
            penalty += con_graph_ptr->nconflicts_for_pair(var_id, neighbor_id) * n;
        }
    }

    return penalty / 2; // counting each edge twice
}


float Penalty::get_penalty() {
    return this->calc_pen();
}