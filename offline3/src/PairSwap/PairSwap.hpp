#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <random>

#include "../Variable/Variable.hpp"
#include "../ConstraintGraph/ConstraintGraph.hpp"

struct PairSwap {
    const ConstraintGraphPtrWk constraint_graph_ptrwk;

    PairSwap(const ConstraintGraphPtrWk);
    std::pair<int, int> get_swappable_pair();
};

using PairSwapPtr = std::shared_ptr<PairSwap>;