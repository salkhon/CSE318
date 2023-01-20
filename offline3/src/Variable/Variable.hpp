#pragma once
#include <memory>

struct Variable {
    int id, nstudents, day;

    Variable(int, int);
};

using VarPtr = std::shared_ptr<Variable>;