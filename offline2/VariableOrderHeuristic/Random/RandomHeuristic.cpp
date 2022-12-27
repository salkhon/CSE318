#include "RandomHeuristic.hpp"

RandomHeuristic::RandomHeuristic(ConstraintGraphPtrWk constraint_graph_ptrwk):
    VariableOrderHeuristic{ constraint_graph_ptrwk } {
    std::srand(std::time(nullptr));
}

VariablePtr RandomHeuristic::next_var() {
    const auto constraint_graph_ptr = this->constraint_graph_ptrwk.lock();
    VariablePtr target_var_ptr = nullptr;

    std::vector<VariablePtr> unassigned;
    std::remove_copy_if(constraint_graph_ptr->var_ptrs.begin(), constraint_graph_ptr->var_ptrs.end(),
        std::back_inserter(unassigned),
        [this](VariablePtr var_ptr) {
            return var_ptr->is_assigned();
        });

    return unassigned[std::rand() % unassigned.size()];
}