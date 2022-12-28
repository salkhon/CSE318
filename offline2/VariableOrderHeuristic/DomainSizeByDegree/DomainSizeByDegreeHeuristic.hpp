#pragma once
#include "../VariableOrderHeuristic.hpp"

struct DomainSizeByDegreeHeuristic: public VariableOrderHeuristic {
    DomainSizeByDegreeHeuristic(const ConstraintGraphPtrWk);
    VariablePtr next_var();
private:
    double score(VariablePtr);
    int degree(VariablePtr);
};