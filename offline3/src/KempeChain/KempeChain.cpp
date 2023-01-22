#include "KempeChain.hpp"

KempeChain::KempeChain(const ConstraintGraphPtrWk constraint_graph_ptrwk)
    : constraint_graph_ptrwk{ constraint_graph_ptrwk } {
}

std::vector<VarPtr> kempechain_using_bfs(ConstraintGraphPtr constraint_graph_ptr, int starting_var_id, int starting_neighbor_id) {
    std::queue<int> q;
    std::vector<VarPtr> kempechain;
    std::vector<bool> is_visited(constraint_graph_ptr->var_ptrs.size(), false);

    int day1 = constraint_graph_ptr->var_ptrs[starting_var_id]->day;
    int day2 = constraint_graph_ptr->var_ptrs[starting_neighbor_id]->day;

    q.push(starting_var_id);
    is_visited[starting_var_id] = true;
    kempechain.push_back(constraint_graph_ptr->var_ptrs[starting_var_id]);

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

std::tuple<std::vector<VarPtr>, int, int> KempeChain::get_random_kempe_chain() {
    auto constraint_graph_ptr = this->constraint_graph_ptrwk.lock();

    int starting_var_id = std::rand() % constraint_graph_ptr->var_ptrs.size();
    int day1 = constraint_graph_ptr->var_ptrs[starting_var_id]->day;

    int nneighbors = constraint_graph_ptr->adj_list[starting_var_id].size();
    if (nneighbors == 0) {
        std::vector<VarPtr> kempechain{{constraint_graph_ptr->var_ptrs[starting_var_id]}};
        return { kempechain, day1, day1 };
    }

    int starting_neighbor_id = constraint_graph_ptr->adj_list[starting_var_id][std::rand() % nneighbors];
    int day2 = constraint_graph_ptr->var_ptrs[starting_neighbor_id]->day;

    // run DFS from that vertex with alternation between day1, day2
    return std::make_tuple(kempechain_using_bfs(constraint_graph_ptr, starting_var_id, starting_neighbor_id), day1, day2);
}
