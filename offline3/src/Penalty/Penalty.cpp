#include "Penalty.hpp"

Penalty::Penalty(const ConstraintGraphPtrWk con_graph_ptrwk)
    : con_graph_ptrwk{ con_graph_ptrwk } {
}

/**
 * @brief Get (5 - n)
 * 
 * @return int (5 - n), where n is the sum of gaps for all neighboring variables
 */
int Penalty::get_sum_of_gap_between_neighbors() {
    auto con_graph_ptr = this->con_graph_ptrwk.lock();
    float penalty = 0;
    int day1, day2;
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
            penalty += std::max(0, 5 - std::abs(day1 - day2));
        }
    }
    return penalty / 2; // counting each edge twice
}
