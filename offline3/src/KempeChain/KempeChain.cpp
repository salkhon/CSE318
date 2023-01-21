#include "KempeChain.hpp"

KempeChain::KempeChain(const ConstraintGraphPtrWk constraint_graph_ptrwk)
    : constraint_graph_ptrwk{ constraint_graph_ptrwk } {
}

std::vector<VarPtr> kempechain_using_dfs(ConstraintGraphPtr constraint_graph_ptr, VarPtr starting_var_ptr, int day1, int day2) {
    std::queue<int> q;
    std::vector<VarPtr> kempechain;
    std::vector<bool> is_visited(constraint_graph_ptr->var_ptrs.size(), false);

    q.push(starting_var_ptr->id);
    is_visited[starting_var_ptr->id] = true;
    kempechain.push_back(starting_var_ptr);

    VarPtr curr_var_ptr, neighbor_var_ptr;
    while (!q.empty()) {
        curr_var_ptr = constraint_graph_ptr->var_ptrs[q.front()];
        q.pop();

        for (auto neighbor_id : constraint_graph_ptr->adj_list[curr_var_ptr->id]) {
            neighbor_var_ptr = constraint_graph_ptr->var_ptrs[neighbor_id];
            if (
                !is_visited[neighbor_id]
                &&
                (
                    (curr_var_ptr->day == day1 && neighbor_var_ptr->day == day2)
                    ||
                    (curr_var_ptr->day == day2 && neighbor_var_ptr->day == day1)
                    )
                ) {

                q.push(neighbor_id);
                is_visited[neighbor_id] = true;
                kempechain.push_back(neighbor_var_ptr);
            }
        }
    }
    return kempechain;
}

VarPtr get_course_assigned_at_day(int day, ConstraintGraphPtr constraint_graph_ptr) {
    size_t start_idx = std::rand() % constraint_graph_ptr->var_ptrs.size();
    size_t sz = constraint_graph_ptr->var_ptrs.size();
    VarPtr target;
    for (size_t i = 0; i < sz; i++) {
        target = constraint_graph_ptr->var_ptrs[(start_idx + i) % sz];
        if (target->day == day) {
            break;
        }
    }
    return target;
}

std::vector<VarPtr> KempeChain::get_kempe_chain(int day1, int day2) {
    auto constraint_graph_ptr = this->constraint_graph_ptrwk.lock();
    // find a course assigned to day1
    VarPtr starting_var_ptr = get_course_assigned_at_day(day1, constraint_graph_ptr);

    // run DFS from that vertex with alternation between day1, day2
    return kempechain_using_dfs(constraint_graph_ptr, starting_var_ptr, day1, day2);
}
