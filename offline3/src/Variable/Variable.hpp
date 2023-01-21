#pragma once
#include <memory>

struct Variable {
    int id, nstudents, day;

    Variable(int, int);
    bool is_day_assigned();
};

using VarPtr = std::shared_ptr<Variable>;