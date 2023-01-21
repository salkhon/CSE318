#pragma once
#include <cstdlib>
#include <time.h>

#include "../ConstraintGraph/ConstraintGraph.hpp"
#include "../ConstructiveHeuristic/ConstructiveHeuristic.hpp"
#include "../ConstructiveHeuristic/LargestDegreeHeuristic/LargestDegreeHeuristic.hpp"
#include "../ConstructiveHeuristic/LargestEnrollmentHeuristic/LargestEnrollmentHeuristic.hpp"
#include "../ConstructiveHeuristic/SaturationDegreeHeuristic/SaturationDegreeHeuristic.hpp"
#include "../Penalty/Penalty.hpp"
#include "../Penalty/LinearPenalty/LinearPenalty.hpp"
#include "../Penalty/ExponentialPenalty/ExponentialPenalty.hpp"
#include "../ConstructiveHeuristic/RandomHeuristic/RandomHeuristic.hpp"
#include "../KempeChain/KempeChain.hpp"
#include "../PairSwap/PairSwap.hpp"

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
    KempePtr kempe_ptr;
    PairSwapPtr pair_swap_ptr;

    size_t nstudents;
    float pen_after_constructive, pen_after_kempe, pen_after_swap;

    Solver(const std::vector<int>&, const std::vector<std::vector<int>>&, PenaltyType, ConstructiveHeuristicType);

    void solve();
    int get_ntimeslots();
    float get_penalty_after_constructive();
    float get_penalty_after_kempe();
    float get_penalty_after_pairswap();

    bool is_sol_correct();
};