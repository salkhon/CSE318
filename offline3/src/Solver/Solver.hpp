#pragma once
#include "../definitions.hpp"

enum ConstructiveHeuristicType {
    LARGEST_DEGREE, LARGEST_ENROLLMENT, SATURATION_DEGREE
};

struct Solver {
    ConstraintGraphPtr constraint_graph_ptr;
    ConHeuPtr con_heu_ptr;
    PerHeuPtr per_heu_ptr;

    Solver(const std::vector<int>&, const std::vector<std::vector<int>>&, ConstructiveHeuristicType);

    void solve();
    int get_ntimeslots();
    float get_penalty_after_constructive();
    float get_penalty_after_kempe();
    float get_penalty_after_pairswap();
};