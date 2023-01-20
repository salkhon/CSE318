#pragma once
#include "../ConstraintGraph/ConstraintGraph.hpp"
#include "../ConstructiveHeuristic/ConstructiveHeuristic.hpp"
#include "../ConstructiveHeuristic/LargestDegreeHeuristic/LargestDegreeHeuristic.hpp"
#include "../ConstructiveHeuristic/LargestEnrollmentHeuristic/LargestEnrollmentHeuristic.hpp"
#include "../ConstructiveHeuristic/SaturationDegreeHeuristic/SaturationDegreeHeuristic.hpp"
#include "../Penalty/Penalty.hpp"
#include "../PerturbativeHeuristic/PerturbativeHeuristic.hpp"
#include "../ConstructiveHeuristic/RandomHeuristic/RandomHeuristic.hpp"

enum ConstructiveHeuristicType {
    LARGEST_DEGREE, LARGEST_ENROLLMENT, SATURATION_DEGREE, RANDOM
};

enum PenaltyType {
    LINEAR, EXPONENTIAL
};

struct Solver {
    ConstraintGraphPtr constraint_graph_ptr;
    PenaltyPtr penalty_ptr;
    ConHeuPtr con_heu_ptr;
    PerHeuPtr per_heu_ptr;

    Solver(const std::vector<int>&, const std::vector<std::vector<int>>&, PenaltyType, ConstructiveHeuristicType);

    void solve();
    int get_ntimeslots();
    float get_penalty_after_constructive();
    float get_penalty_after_kempe();
    float get_penalty_after_pairswap();
};