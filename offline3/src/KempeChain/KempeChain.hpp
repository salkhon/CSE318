#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <queue>

#include "../Variable/Variable.hpp"
#include "../ConstraintGraph/ConstraintGraph.hpp"

struct KempeChain {
    const ConstraintGraphPtrWk constraint_graph_ptrwk;

    KempeChain(const ConstraintGraphPtrWk);
    std::vector<VarPtr> get_kempe_chain(int, int);
};

using KempePtr = std::shared_ptr<KempeChain>;
