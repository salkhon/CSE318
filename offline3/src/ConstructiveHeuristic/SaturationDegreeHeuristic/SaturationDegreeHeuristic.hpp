#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <queue>

#include "../../Variable/Variable.hpp"
#include "../../ConstraintGraph/ConstraintGraph.hpp"
#include "../ConstructiveHeuristic.hpp"

struct SaturationDegreeHeuristic: public ConstructiveHeuristic {
    SaturationDegreeHeuristic(const ConstraintGraphPtrWk);
    void assign_variables_in_order();
private:
    std::vector<bool> is_day_assigned;
    int get_ndays_in_neighbors(VarPtr, ConstraintGraphPtr);
};

using SatHeuPtr = std::shared_ptr<SaturationDegreeHeuristic>;