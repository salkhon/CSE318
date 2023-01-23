#pragma once
#include <memory>
#include <ostream>

struct Variable {
    int id, nstudents, day;

    Variable(int, int);
    bool is_day_assigned();
    friend std::ostream& operator<< (std::ostream& ostrm, const Variable& var);
};

using VarPtr = std::shared_ptr<Variable>;