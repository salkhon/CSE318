#include "Solver.hpp"

std::vector<VarPtr> _create_vars(const std::vector<int>& course_nstudents) {
    std::vector<VarPtr> var_ptrs(course_nstudents.size());
    for (size_t i = 0; i < course_nstudents.size(); i++) {
        var_ptrs[i] = std::make_shared<Variable>(i, course_nstudents[i]);
    }
    return var_ptrs;
}

ConHeuPtr _create_constructive_heuristic_ptr(ConstructiveHeuristicType type, const std::vector<VarPtr>& var_ptrs) {
    ConHeuPtr con_heu_ptr = nullptr;
    if (type == LARGEST_DEGREE) {
        con_heu_ptr = std::make_shared<LargestDegreeHeuristic>(var_ptrs);
    } else if (type == LARGEST_ENROLLMENT) {
        con_heu_ptr = std::make_shared<LargestEnrollmentHeuristic>(var_ptrs);
    } else if (type == SATURATION_DEGREE) {
        con_heu_ptr = std::make_shared<SaturationDegreeHeuristic>(var_ptrs);
    }
    return con_heu_ptr;
}

Solver::Solver(
    const std::vector<int>& course_nstudents,
    const std::vector<std::vector<int>>& student_courses,
    ConstructiveHeuristicType constructive_heuristic_type
)
    : constraint_graph_ptr{ std::make_shared<ConstraintGraph>(_create_vars(course_nstudents)) },
    con_heu_ptr{ _create_constructive_heuristic_ptr(constructive_heuristic_type, this->constraint_graph_ptr->var_ptrs) } {

    for (const auto& courses : student_courses) {
        for (size_t i = 0; i < courses.size(); i++) {
            for (size_t j = i + 1; j < courses.size(); j++) {
                constraint_graph_ptr->add_edge(courses[i], courses[j]);
            }
        }
    }
}

/**
 * @brief
 * 1. Place the courses without conflict
 *      Solve hard constraint with constructuve heuristic
 *      - Start with one color (day 1)
 *      - If the next exam conflicts, increase day count
 * 2. Search to minimize penalty
 *      Solve soft constraint with perturbative heuristic
 *
 */
void Solver::solve() {
    int newday = 0;
    const auto& var_ptrs_order = this->con_heu_ptr->get_var_order();
    for (size_t i = 0; i < var_ptrs_order.size(); i++) {
        // find non conflicting course that was previously assigned
        auto non_adj_var_ptr = *std::find_if_not(var_ptrs_order.begin(), var_ptrs_order.begin() + i,
            [this, &var_ptrs_order, i](VarPtr assigned_var_ptr) {
                return this->constraint_graph_ptr->is_adj(var_ptrs_order[i]->id, assigned_var_ptr->id);
            }
        );

        if (non_adj_var_ptr != var_ptrs_order[i]) {
            // assign previous day to var i
            var_ptrs_order[i]->day = non_adj_var_ptr->day;
        } else {
            // assign new day to var i
            var_ptrs_order[i]->day = newday++;
        }
    }
}

int Solver::get_ntimeslots() {
    return 0;
}

float Solver::get_penalty_after_constructive() {
    return 0.0f;
}

float Solver::get_penalty_after_kempe() {
    return 0.0f;
}

float Solver::get_penalty_after_pairswap() {
    return 0.0f;
}
