#pragma once
#include "../Penalty.hpp"

struct LinearPenalty: public Penalty {
    LinearPenalty(const ConstraintGraphPtrWk);
    float apply(int);
};