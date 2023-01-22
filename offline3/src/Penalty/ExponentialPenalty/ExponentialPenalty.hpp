#pragma once
#include "../Penalty.hpp"
#include <cmath>

struct ExponentialPenalty: public Penalty {
    ExponentialPenalty(const ConstraintGraphPtrWk);
    float apply(int);
};