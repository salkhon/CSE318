#include "SaturationDegreeHeuristic.hpp"

SaturationDegreeHeuristic::SaturationDegreeHeuristic(const ConstraintGraphPtrWk con_graph_ptrwk)
    : ConstructiveHeuristic{ con_graph_ptrwk } {
}

std::vector<VarPtr> SaturationDegreeHeuristic::get_var_order() {
    auto con_graph_ptr = this->con_graph_ptrwk.lock();
    std::vector<VarPtr> ordered_var_ptrs{ con_graph_ptr->var_ptrs };
    std::vector<int> npicked(ordered_var_ptrs.size(), 0);

    // selecting all var_ptrs.size() number of variables
    for (size_t i = 0; i < ordered_var_ptrs.size(); i++) {
        // node with largest assigned neighbor
        auto var_ptr_iter = std::max_element(ordered_var_ptrs.begin() + i, ordered_var_ptrs.end(),
            [&npicked, con_graph_ptr](VarPtr v1, VarPtr v2) {
                return (
                    npicked[v1->id] < npicked[v2->id]
                    ||
                    (npicked[v1->id] == npicked[v2->id] && con_graph_ptr->degree(v1->id) < con_graph_ptr->degree(v2->id))
                    );
            }
        );

        // incrementing assign count for picked node's neighbor
        for (auto neighbor : con_graph_ptr->adj_list[(*var_ptr_iter)->id]) {
            npicked[neighbor]++;
        }

        std::iter_swap(ordered_var_ptrs.begin() + i, var_ptr_iter);
    }

    return ordered_var_ptrs;
}
