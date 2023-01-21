#pragma once
#include "../Penalty.hpp"

struct ExponentialPenalty: public Penalty {
    ExponentialPenalty(const ConstraintGraphPtrWk);
    double get_penalty();
};