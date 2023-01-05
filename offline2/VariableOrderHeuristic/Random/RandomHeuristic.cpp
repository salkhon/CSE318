#include "RandomHeuristic.hpp"

RandomHeuristic::RandomHeuristic(const ConstraintGraphPtrWk constraint_graph_ptrwk):
    VariableOrderHeuristic{ constraint_graph_ptrwk } {
    std::srand(std::time(nullptr));
}

VariablePtr RandomHeuristic::next_var() {
    const auto constraint_graph_ptr = this->constraint_graph_ptrwk.lock();

    int random_unassigned_idx = std::rand() % constraint_graph_ptr->get_num_unassigned_var();
    int idx = 0;
    VariablePtr target_var_ptr = nullptr;
    for (auto var_ptr : constraint_graph_ptr->var_ptrs) {
        if (!var_ptr->is_assigned() && idx++ == random_unassigned_idx) {
            target_var_ptr = var_ptr;
            break;
        }
    }
    return target_var_ptr;
}