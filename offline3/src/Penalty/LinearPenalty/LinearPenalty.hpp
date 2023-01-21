#pragma once
#include "../Penalty.hpp"

struct LinearPenalty: public Penalty {
    LinearPenalty(const ConstraintGraphPtrWk);
    double get_penalty();
};