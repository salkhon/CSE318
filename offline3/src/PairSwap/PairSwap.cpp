#include "PairSwap.hpp"

PairSwap::PairSwap(const ConstraintGraphPtrWk constraint_graph_ptrwk)
    : constraint_graph_ptrwk{ constraint_graph_ptrwk } {
}

bool is_swappable(int v1, int v2, ConstraintGraphPtr constraint_graph_ptr) {
    const auto& adj1 = constraint_graph_ptr->adj_list[v1], & adj2 = constraint_graph_ptr->adj_list[v2];
    return std::find_if(adj1.begin(), adj1.end(),
        [constraint_graph_ptr, v2](int neighbor2_id) {
            return constraint_graph_ptr->var_ptrs[neighbor2_id]->day == constraint_graph_ptr->var_ptrs[v2]->day;
        }
    ) == adj1.end()
            &&
            std::find_if(adj2.begin(), adj2.end(),
                [constraint_graph_ptr, v1](int neighbor2_id) {
                    return constraint_graph_ptr->var_ptrs[neighbor2_id]->day == constraint_graph_ptr->var_ptrs[v1]->day;
                }
        ) == adj2.end(); // v1 s neighbors don't have v2's day assigned and vice versa
}

std::pair<int, int> PairSwap::get_swappable_pair() {
    auto constraint_graph_ptr = this->constraint_graph_ptrwk.lock();
    int n = 10;
    while (n--) {
        int v1 = std::rand() % constraint_graph_ptr->var_ptrs.size();
        int v2 = std::rand() % constraint_graph_ptr->var_ptrs.size();
        if (v1 != v2 && is_swappable(v1, v2, constraint_graph_ptr)) {
            return std::make_pair(v1, v2);
        }
    }
    return std::make_pair(-1, -1); // no pair found after 10 tries
}