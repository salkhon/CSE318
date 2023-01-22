#include "SaturationDegreeHeuristic.hpp"

SaturationDegreeHeuristic::SaturationDegreeHeuristic(const ConstraintGraphPtrWk constraint_graph_ptrwk)
    : ConstructiveHeuristic{ constraint_graph_ptrwk },
    is_day_assigned(constraint_graph_ptrwk.lock()->var_ptrs.size(), false) {
}

int SaturationDegreeHeuristic::get_ndays_in_neighbors(VarPtr var_ptr, ConstraintGraphPtr constraint_graph_ptr) {
    // counts number of unique days in neighbors of var_ptr
    std::fill(is_day_assigned.begin(), is_day_assigned.end(), false);

    for (auto neighbor_id : constraint_graph_ptr->adj_list[var_ptr->id]) {
        if (!constraint_graph_ptr->var_ptrs[neighbor_id]->is_day_assigned()) {
            continue;
        }
        is_day_assigned[constraint_graph_ptr->var_ptrs[neighbor_id]->day] = true;
    }

    return std::count(is_day_assigned.begin(), is_day_assigned.end(), true);
}

void SaturationDegreeHeuristic::assign_variables_in_order() {
    auto constraint_graph_ptr = this->constraint_graph_ptrwk.lock();

    // pq to be updated with each assignment
    auto pq_cmp = [this, constraint_graph_ptr](VarPtr v1, VarPtr v2) {
        return this->get_ndays_in_neighbors(v1, constraint_graph_ptr) < this->get_ndays_in_neighbors(v2, constraint_graph_ptr);
    }; // max heap by default

    std::vector<VarPtr> pq{ constraint_graph_ptr->var_ptrs };
    std::make_heap(pq.begin(), pq.end(), pq_cmp);

    VarPtr var_ptr;
    while (!pq.empty()) {
        var_ptr = pq.front();
        std::pop_heap(pq.begin(), pq.end(), pq_cmp);
        pq.pop_back();

        var_ptr->day = this->get_lowest_assignagble_day(var_ptr);

        // update pq keys
        std::make_heap(pq.begin(), pq.end(), pq_cmp);
    }
}
