#pragma once
#include <vector>
#include <memory>

#include "../ConstraintGraph/ConstraintGraph.hpp"

struct Penalty {
    const ConstraintGraphPtrWk con_graph_ptrwk;

    Penalty(const ConstraintGraphPtrWk);
    float get_penalty();
protected:
    float calc_pen();
    virtual float apply(int) = 0;
};

using PenaltyPtr = std::shared_ptr<Penalty>;