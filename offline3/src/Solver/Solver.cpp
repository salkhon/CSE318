#include "Solver.hpp"
#include <iostream>

ConstraintGraphPtr _create_constraint_graph_ptr(const std::vector<int>& course_nstudents) {
    std::vector<VarPtr> var_ptrs(course_nstudents.size());
    for (size_t i = 0; i < course_nstudents.size(); i++) {
        var_ptrs[i] = std::make_shared<Variable>(i, course_nstudents[i]);
    }
    return std::make_shared<ConstraintGraph>(var_ptrs);
}

ConHeuPtr _create_constructive_heuristic_ptr(ConstructiveHeuristicType contype, ConstraintGraphPtr constraint_graph_ptr) {
    ConHeuPtr constructive_heu_ptr = nullptr;
    if (contype == LARGEST_DEGREE) {
        constructive_heu_ptr = std::make_shared<LargestDegreeHeuristic>(constraint_graph_ptr);
    } else if (contype == LARGEST_ENROLLMENT) {
        constructive_heu_ptr = std::make_shared<LargestEnrollmentHeuristic>(constraint_graph_ptr);
    } else if (contype == SATURATION_DEGREE) {
        constructive_heu_ptr = std::make_shared<SaturationDegreeHeuristic>(constraint_graph_ptr);
    } else if (contype == RANDOM) {
        constructive_heu_ptr = std::make_shared<RandomHeuristic>(constraint_graph_ptr);
    }
    return constructive_heu_ptr;
}

PenaltyPtr _create_penalty_ptr(PenaltyType pentype, ConstraintGraphPtr constraint_graph_ptr) {
    PenaltyPtr penptr = nullptr;
    if (pentype == LINEAR) {
        penptr = std::make_shared<LinearPenalty>(constraint_graph_ptr);
    } else if (pentype == EXPONENTIAL) {
        penptr = std::make_shared<ExponentialPenalty>(constraint_graph_ptr);
    }
    return penptr;
}

Solver::Solver(
    const std::vector<int>& course_nstudents,
    const std::vector<std::vector<int>>& student_courses,
    PenaltyType penalty_type,
    ConstructiveHeuristicType constructive_heuristic_type
)
    : constraint_graph_ptr{ _create_constraint_graph_ptr(course_nstudents) },
    penalty_ptr{ _create_penalty_ptr(penalty_type, this->constraint_graph_ptr) },
    constructive_heu_ptr{ _create_constructive_heuristic_ptr(constructive_heuristic_type, this->constraint_graph_ptr) },
    kempe_ptr{ std::make_shared<KempeChain>(this->constraint_graph_ptr) },
    pair_swap_ptr{ std::make_shared<PairSwap>(this->constraint_graph_ptr) },
    nstudents{ student_courses.size() }, pen_after_constructive{ -1 }, pen_after_kempe{ -1 }, pen_after_swap{ -1 } {

    for (const auto& courses : student_courses) {
        for (size_t i = 0; i < courses.size(); i++) {
            for (size_t j = i + 1; j < courses.size(); j++) {
                this->constraint_graph_ptr->add_edge(courses[i], courses[j]);
            }
        }
    }
}

void swap_kempechain_day(std::vector<VarPtr>& var_ptrs, int day1, int day2) {
    for (auto var_ptr : var_ptrs) {
        if (var_ptr->day == day1) {
            var_ptr->day = day2;
        } else {
            var_ptr->day = day1;
        }
    }
}

bool is_kempe_chain_correct(const std::vector<VarPtr>& varptrs) {
    std::vector<int> days;
    for (auto varptr : varptrs) {
        if (std::find(days.begin(), days.end(), varptr->day) == days.end()) {
            days.push_back(varptr->day);
        }
    }
    return days.size() == 2;
}

void Solver::solve() {
    // CONSTRUCTIVE
    this->constructive_heu_ptr->assign_variables_in_order();

    this->pen_after_constructive = this->penalty_ptr->get_penalty() / this->nstudents;
    int totaldays = this->get_ntimeslots();
    float curr_pen, prev_pen = this->pen_after_constructive;

    // KEMPE CHAIN
    for (size_t i = 0; i < 1000; i++) {
        auto [kempechain, day1, day2] = this->kempe_ptr->get_random_kempe_chain();
        if (kempechain.size() == 1) {
            continue;
        }
        swap_kempechain_day(kempechain, day1, day2);

        curr_pen = this->penalty_ptr->get_penalty() / this->nstudents;
        if (curr_pen > prev_pen) {
            swap_kempechain_day(kempechain, day1, day2); // undo swap
        } else {
            prev_pen = curr_pen;
        }
    }
    this->pen_after_kempe = prev_pen;

    // PAIR SWAP
    for (size_t i = 0; i < 1000; i++) {
        auto [v1, v2] = this->pair_swap_ptr->get_swappable_pair();
        if (v1 >= 0 && v2 >= 0) {
            std::swap(this->constraint_graph_ptr->var_ptrs[v1]->day, this->constraint_graph_ptr->var_ptrs[v2]->day);
            curr_pen = this->penalty_ptr->get_penalty() / this->nstudents;
            if (curr_pen > prev_pen) {
                std::swap(this->constraint_graph_ptr->var_ptrs[v1]->day, this->constraint_graph_ptr->var_ptrs[v2]->day); // undo
            } else {
                prev_pen = curr_pen;
            }
        }
    }

    this->pen_after_swap = this->penalty_ptr->get_penalty() / this->nstudents;
}

int Solver::get_ntimeslots() {
    auto max_day_var_ptr = *std::max_element(this->constraint_graph_ptr->var_ptrs.begin(), this->constraint_graph_ptr->var_ptrs.end(),
        [](VarPtr v1, VarPtr v2) {
            return v1->day < v2->day;
        }
    );
    return max_day_var_ptr->day;
}

float Solver::get_penalty_after_constructive() {
    return this->pen_after_constructive;
}

float Solver::get_penalty_after_kempe() {
    return this->pen_after_kempe;
}

float Solver::get_penalty_after_pairswap() {
    return this->pen_after_swap;
}

bool Solver::is_sol_correct() {
    for (auto var_ptr : this->constraint_graph_ptr->var_ptrs) {
        for (auto neighbor_id : this->constraint_graph_ptr->adj_list[var_ptr->id]) {
            if (var_ptr->day == this->constraint_graph_ptr->var_ptrs[neighbor_id]->day) {
                // course and constraint neighbor has the same day
                return false;
            }
        }
    }
    return true;
}
