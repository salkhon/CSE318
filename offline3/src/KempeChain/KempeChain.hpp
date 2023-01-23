#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <tuple>

#include "../Variable/Variable.hpp"
#include "../ConstraintGraph/ConstraintGraph.hpp"

struct KempeChain {
    const ConstraintGraphPtrWk constraint_graph_ptrwk;

    KempeChain(const ConstraintGraphPtrWk);
    std::tuple<std::vector<VarPtr>, int, int> get_random_kempe_chain();
};

using KempePtr = std::shared_ptr<KempeChain>;
