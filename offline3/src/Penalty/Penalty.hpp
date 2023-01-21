#pragma once
#include <vector>
#include <memory>

#include "../ConstraintGraph/ConstraintGraph.hpp"

struct Penalty {
    const ConstraintGraphPtrWk con_graph_ptrwk;

    Penalty(const ConstraintGraphPtrWk);
    virtual double get_penalty() = 0;
};

using PenaltyPtr = std::shared_ptr<Penalty>;